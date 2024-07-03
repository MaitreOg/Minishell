/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:23:51 by smarty            #+#    #+#             */
/*   Updated: 2024/06/01 01:07:25 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_verif(char *str, int i)
{
	int	double_open;
	int	simple_open;
	int	y;

	double_open = 0;
	simple_open = 0;
	y = 0;
	while (y < i)
	{
		if (str[y] == '\'' && simple_open == 0)
			simple_open = 1;
		else if (str[y] == '"' && double_open == 0)
			double_open = 1;
		else if (str[y] == '\'' && simple_open == 1)
			simple_open = 0;
		else if (str[y] == '"' && double_open == 1)
			double_open = 0;
		y++;
	}
	if (simple_open == 1 || double_open == 1)
		return (1);
	return (0);
}

int	is_verif_quotes(char *str, int i)
{
	int	simple_open;
	int	y;

	simple_open = 0;
	y = 0;
	while (y < i)
	{
		if (str[y] == '\'' && is_verif_double(str, y) == 0 && simple_open == 0)
		{
			simple_open = 1;
			y++;
		}
		if (str[y] == '\'' && is_verif_double(str, y) == 0 && simple_open == 1)
			simple_open = 0;
		y++;
	}
	if (simple_open == 1)
		return (1);
	return (0);
}

int	is_verif_double(char *str, int i)
{
	int	double_open;
	int	y;

	double_open = 0;
	y = 0;
	while (y < i)
	{
		if (str[y] == '"' && is_verif_quotes(str, y) == 0 && double_open == 0)
		{
			double_open = 1;
			y++;
		}
		if (str[y] == '"' && is_verif_quotes(str, y) == 0 && double_open == 1)
			double_open = 0;
		y++;
	}
	if (double_open == 1)
		return (1);
	return (0);
}

char	*delete_quotes(char *str)
{
	int		i;
	int		y;
	char	*line;
	char	*line2;
	char	*tmp;

	i = -1;
	y = 0;
	tmp = ft_strdup_v2(str);
	while (str[++i])
	{
		if ((str[i] == '\'' && is_verif_double(tmp, y) == 0)
			|| (str[i] == '"' && is_verif_quotes(tmp, y) == 0))
		{
			str[i] = 0;
			line = ft_strdup_v2(str);
			line2 = ft_strdup_v2(&str[i + 1]);
			free(str);
			str = ft_strjoin(line, line2, 1, 1);
			i--;
		}
		y++;
	}
	free (tmp);
	return (str);
}
