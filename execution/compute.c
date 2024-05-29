/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:59:45 by smarty            #+#    #+#             */
/*   Updated: 2024/05/30 01:35:53 by smarty           ###   ########.fr       */
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
	if (tmp->content_type == TYPE_ROUT)
        redirect_output(data, tmp->next, 0);
	else if (tmp->content_type == TYPE_ROUT_APP)
        redirect_output(data, tmp->next, 1);
    else if (tmp->content_type == TYPE_RIN)
        redirect_input(data, tmp->next);
	else if (tmp->content_type == TYPE_LIMITER)
        limiter(data, tmp->next);
}

void compute_operator(t_data *data, t_list *lst)
{
    t_list *tmp;
    t_list *order;
    
    order = lst;
    tmp = lst->next;
    while (tmp && tmp->content_type != 0)
    {
        if (tmp->content_type > 0 && tmp->content_type < 6)
            link_io(data, order, tmp);
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
            data->execute = 0;
            compute_operator(data, lst);
            if (data->execute == 0)
            {
                fork_order(data, lst);
            }
            data->o = 0;
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