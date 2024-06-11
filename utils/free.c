/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 22:25:36 by smarty            #+#    #+#             */
/*   Updated: 2024/06/08 22:15:55 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_tab(char **tab)
{
    int i;

    i = -1;
    while(tab[++i])
    	free(tab[i]);
    free(tab);
}

void    free_lst(t_list *lst)
{
    t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free (lst);
		lst = tmp;
	}
}

void free_compute(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->line_lst)
		free_lst(data->line_lst);
	free(data->childpid);
}

void free_all(t_data *data)
{
    if (data->env)
        free_tab(data->env);
    if (data->line)
        free(data->line);
    if (data->line_lst)
      free_lst(data->line_lst);
	free(data->childpid);
}
