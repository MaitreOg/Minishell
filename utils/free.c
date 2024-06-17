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

    if (!tab)
		return ;
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
		lst->content = NULL;
		free (lst);
		lst = tmp;
	}
	lst = NULL;
}

void ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *tmp;

	while(lst)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void free_compute(t_data *data)
{
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->line_lst)
	{
		free_lst(data->line_lst);
	}
	if (data->childpid)
	{
		free(data->childpid);
		data->childpid = NULL;
	}
}

void free_all(t_data *data)
{
    if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->line_lst)
	{
		free_lst(data->line_lst);
	}
	if (data->childpid)
	{
		free(data->childpid);
		data->childpid = NULL;
	}
}
