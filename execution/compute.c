/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:59:45 by smarty            #+#    #+#             */
/*   Updated: 2024/05/29 17:11:13 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void link_io(t_data *data, t_list *lst)
{
    if (lst->content_type == TYPE_PIPE)
        pipes(lst , lst, data); //redirige uniquement out/in
	else if (lst->content_type == TYPE_ROUT)
        redirect_output(data, lst->next, 0);
	else if (lst->content_type == TYPE_ROUT_APP)
        redirect_output(data, lst->next, 1);
    else if (lst->content_type == TYPE_RIN)
        redirect_input(data, lst->next);
	else if (lst->next->content_type == TYPE_LIMITER)
        limiter(data, lst->next);
}

void compute_operator(t_data *data, t_list *lst)
{
    t_list *tmp;
    
    tmp = lst->next;
    while (tmp && tmp->content_type != 0)
    {
        if (tmp->content_type > 0 && tmp->content_type < 6)
            link_io(data, tmp);
        tmp = tmp->next;
    }
}

void compute(t_data *data)
{
    t_list *lst;
    
    lst = data->line_lst;
    while (lst)
    {
        if(lst->content_type == 0)
        {
            compute_operator(data, lst);
            execute(data, lst);
        }
        lst = lst->next;
    }
}
/*
void compute(t_data *data)
{
    t_list *lst;
    
    lst = data->line_lst;
    while (lst)
    {
        if(lst->next->content_type == 5)
        {
            //pipes(lst_prev_order(lst, data->line_lst), lst->next->next, data);
        }
        else
        {
            if (lst->next && lst->next->content_type >= 1 && lst->next->content_type <= 4)
                compute_operator(data, lst);
            compute_commande(data, lst);
        }
        lst = lst->next;
    }
}*/