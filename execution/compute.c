/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:59:45 by smarty            #+#    #+#             */
/*   Updated: 2024/05/25 23:23:53 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void compute_operator(t_data *data, t_list *lst)
{
    if (lst->content_type == TYPE_RIN)
        redirect_input(data, lst);
	else if (lst->content_type == TYPE_LIMITER)
        limiter(data, lst);
	else if (lst->content_type == TYPE_ROUT)
        redirect_output(data, lst);
	else if (lst->content_type == TYPE_ROUT_APP)
        redirect_output_a(data, lst);
}

void compute_commande(t_data *data, t_list *lst)
{
    
}

void compute(t_data *data)
{
    t_list *lst;
    
    lst = data->line_lst;
    while (lst)
    {
        if(lst->next->content_type == 5)
        {
        }
        else
        {
            if (lst->next->content_type >= 1 && lst->next->content_type <= 4)
                compute_operator(data, lst);
            compute_commande(data, lst);
        }
        lst = lst->next;
    }
}