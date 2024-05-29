/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:29:14 by smarty            #+#    #+#             */
/*   Updated: 2024/05/29 17:12:27 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_type(t_list *lst, t_list *original)
{
	if (ft_strcmp("<", lst->content) == 1)
		lst->content_type = TYPE_RIN;
	else if (ft_strcmp("<<", lst->content) == 1)
		lst->content_type = TYPE_LIMITER;
	else if (ft_strcmp(">", lst->content) == 1)
		lst->content_type = TYPE_ROUT;
	else if (ft_strcmp(">>", lst->content) == 1)
		lst->content_type = TYPE_ROUT_APP;
	else if (ft_strcmp("|", lst->content) == 1)
		lst->content_type = TYPE_PIPE;
	else if (lst_prev(lst, original))
	{
		if (lst_prev(lst, original)->content_type == TYPE_ROUT || lst_prev(lst, original)->content_type == TYPE_ROUT_APP || lst_prev(lst, original)->content_type == TYPE_RIN)
			lst->content_type = TYPE_FILE;
	}
	else
		lst->content_type = TYPE_ORDER;
}

void	token_to_lst(char **tab, t_data *data)
{
	int i;

	i = -1;
	data->line_lst = malloc(sizeof(t_list));
	while(tab[++i])
	{
		data->line_lst = lst_add(data->line_lst, tab[i]);
	}
}
void add_necessary(t_data *data)
{
	t_list *tmp;
	
	tmp = data->line_lst;
	while(tmp)
	{
		tmp->content = delete_quotes(tmp->content);
		tmp->content = replace_var(data, tmp->content);
		add_type(tmp, data->line_lst);
		tmp = tmp->next;
	}
}

void    line_to_token(t_data *data)
{
	char **tab;
	int i;

	tab = ft_split2(data->line, "|<>");
	token_to_lst(tab, data);
	if (data->line_lst->content == NULL)
		printf("le debut de la liste est null\n");
	add_necessary(data); //ajoute le type et supprime les quotes et remplace les $
	//ft_lstprint(data->line_lst);
}
