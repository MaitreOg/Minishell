/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:29:14 by smarty            #+#    #+#             */
/*   Updated: 2024/05/21 17:26:44 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
void    cut_order(char *string, t_token *token)
{
	if (string[0] == '<' || string[0] == '>' || string[0] == '|')
		token->type = 2;
	else
		token->type = 1;
}
void	add_type(t_token *token, int i)
{
	if (token[i].order[0] == '>>' || token[i].order[0] == '>')
		token[i].type = 2;
	else if (token[i].order[0] == '|')
		token[i].type = 3;
	else if (i > 0 && token[i - 1].type == 2)
		token[i].type = 4;
	else
		token[i].type = 1;
}

t_token	*convert_to_struct(char ***tab)
{
	int	i;
	int	y;
	int	z;
	t_token *token;
	
	i = -1;
	z = 0;
	while(tab[++i])
	{
		y = -1;
		while(tab[i][++y])
			z++;
	}
	i = -1;
	token = malloc(sizeof(t_token) * z);
	z = 0;
	while(tab[++i])
	{
		y = -1;
		while(tab[i][++y])
		{	
			token[z].order = ft_strdup(tab[i][y]);
			//cut_order(token[z].order, &token[z]);
			add_type(token, z);
			token[z].order = delete_quotes(token[z].order);
			printf("z : %d\ttype : %d\tstring :%s\n", z, token[z].type, token[z].order);
			z++;
		}
	}
	return (token);
}

void    line_to_token(t_data *data)
{
	char **tab_pipe;
	char ***tab_redirection;
	int i;
	int y;
	int	z;
	t_token *token;

	i = 0;
	tab_pipe = ft_split2(data->line, "|");
	while(tab_pipe[i])
		i++;
	tab_redirection = malloc(sizeof(char **) *  (i + 1));
	i = -1;
	while(tab_pipe[++i])
		tab_redirection[i] = ft_split2(tab_pipe[i], "><");
	tab_redirection[i] = NULL;
	token = convert_to_struct(tab_redirection);
}
