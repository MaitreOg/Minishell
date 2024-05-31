/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:59:45 by smarty            #+#    #+#             */
/*   Updated: 2024/05/31 21:52:17 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void link_io(t_data *data,t_list *order, t_list *tmp)
{
    if (tmp->content_type == TYPE_PIPE)
    {
        data->execute = 1;
        pipes(data, order);
    }
    else if (tmp->content_type == TYPE_LIMITER)
        limiter(data, tmp->next);
	else if (tmp->content_type == TYPE_ROUT)
        redirect_output(data, tmp->next, 0);
	else if (tmp->content_type == TYPE_ROUT_APP)
        redirect_output(data, tmp->next, 1);
    else if (tmp->content_type == TYPE_RIN)
        redirect_input(data, tmp->next);
}

void compute_operator(t_data *data, t_list *lst)
{
    t_list *tmp;
    t_list *order;

    order = lst;
    tmp = lst->next;
    
    while (tmp && tmp->content_type != 0 && data->in_progress == 1)
    {
        if (tmp->content_type > 0 && tmp->content_type < 6)
            link_io(data, order, tmp);
        tmp = tmp->next;
    }
}

void compute(t_data *data)
{
    t_list *lst;
    int stdout_backup;
    int stdin_backup;
    
	stdout_backup = dup(STDOUT_FILENO);
	stdin_backup = dup(STDIN_FILENO);
    lst = data->line_lst;
    while (lst && data->in_progress == 1)
    {
        data->fdo = stdout_backup;
        if(lst->content_type == 0)
        {
            data->execute = 0;
            compute_operator(data, lst);
            data->o = 0;
            if (data->execute == 0 && data->in_progress == 1)
            {
                fork_order(data, lst);
            }
            dup2(stdout_backup, STDOUT_FILENO);
            if (data->execute == 0)
                dup2(stdin_backup, STDIN_FILENO);
        }
        lst = lst->next;
    }
    close(stdout_backup);
    close(stdin_backup);
}
