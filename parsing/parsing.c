/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:29:14 by smarty            #+#    #+#             */
/*   Updated: 2024/05/23 18:12:02 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	add_type(t_list *lst)
{
	if (token[i].order[0] == '<' || token[i].order[0] == '>')
		token[i].type = 2;
	else if (token[i].order[0] == '|')
		token[i].type = 3;
	else if (i > 0 && token[i - 1].type == 2)
		token[i].type = 4;
	else
		token[i].type = 1;
}*/

void	token_to_lst(char **tab, t_data *data)
{
	int i;

	i = -1;
	if (data->line_lst)
		free (data->line_lst);
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
	ft_lstprint(data->line_lst);
}
