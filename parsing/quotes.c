/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:23:51 by smarty            #+#    #+#             */
/*   Updated: 2024/04/04 21:08:40 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_verif(char *str, int i)
{
	int	double_open;
	int	simple_open;
	int	y;

	double_open = 0;
	simple_open = 0;
	y = 0;
	while(y < i)
	{
		if (str[y] == '\'' && simple_open == 0)
		{
			simple_open = 1;
			y++;
		}
		if (str[y] == '"' && double_open == 0)
		{
			y++;
			double_open = 1;
		}
		if (str[y] == '\'' && simple_open == 1)
			simple_open = 0;
		if (str[y] == '"' && double_open == 1)
			double_open = 0;
		y++;
	}
	if (simple_open == 1 || double_open == 1)
		return (1);
	return(0);
}

int is_verif_quotes(char *str, int i)
{
	int	simple_open;
	int	y;

	simple_open = 0;
	y = 0;
	while(y < i)
	{
		if (str[y] == '\'' && simple_open == 0)
		{
			simple_open = 1;
			y++;
		}
		if (str[y] == '\'' && simple_open == 1)
			simple_open = 0;
		y++;
	}
	if (simple_open == 1)
		return (1);
	return(0);
}

char	*delete_quotes(char *str)
{
	int	i;
	int	y;
	char	*line;
	char	*line2;

	i = 0;
	while (str[i])
	{
		y = 0;
		while (str[i] != '\'' && str[i] != '"' && str[i] )
			i++;
		if (str[i] == '\'' || str[i] == '"')
		{
			str[i] = 0;
			line = ft_strdup(str);
			line2 = ft_strdup(&str[i + 1]);
			line = ft_strjoin(line, line2);
			free(str);
			str = ft_strdup(line);
			free (line);
			free (line2);
		}
	}
	return (str);
}
