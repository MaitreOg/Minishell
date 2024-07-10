/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:37:37 by oliradet          #+#    #+#             */
/*   Updated: 2024/07/03 16:37:37 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_operator(char *str, int y, char *operator)
{
	int	i;

	i = -1;
	while (operator[++i])
	{
		if (operator[i] == str[y] && is_verif(str, y) == 0)
			return (1);
	}
	return (0);
}

int	count_word2(char *str, char *operator)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (str[0] == 0)
		return (0);
	while (str[i])
	{
		if (check_operator(str, i, operator) == 1
			&& ((check_operator(str, (i + 1), operator) == 0 && str[i + 1])
				|| str[i + 1] == 0))
			nb += 1;
		if (check_operator(str, i, operator) == 0
			&& ((check_operator(str, (i + 1), operator) == 1 && str[i + 1])
				|| str[i + 1] == 0))
			nb += 1;
		i++;
	}
	return (nb);
}

char	*copy_word(char *operator, char *str, int i)
{
	int		y;
	char	*split;

	y = 0;
	while (check_operator(str, (i + y), operator) == 0 && str[i + y])
		y++;
	if (y > 0)
		split = (char *)malloc (sizeof(char) * (y + 1));
	y = 0;
	while (check_operator(str, i, operator) == 0 && str[i])
	{
		split[y] = str[i];
		y++;
		i++;
	}
	split[y] = '\0';
	return (split);
}

char	*copy_sep(char *operator, char *str, int i)
{
	int		y;
	char	*split;

	y = 0;
	while (check_operator(str, (i + y), operator) == 1 && str[i + y])
		y++;
	split = (char *)malloc (sizeof(char) * (y + 1));
	y = 0;
	while (check_operator(str, i, operator) == 1 && str[i])
		split[y++] = str[i++];
	split[y] = 0;
	while (str[i] == ' ')
		i++;
	return (split);
}

char	**cut_split_2(char *str, char **split, char *operator)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (check_operator(str, i, operator) == 0)
			split[word] = copy_word(operator, str, i);
		if (check_operator(str, i, operator) == 0)
			word++;
		while (check_operator(str, i, operator) == 0 && str[i])
			i++;
		if (str[i] == 0)
		{
			split[word] = NULL;
			return (split);
		}
		split[word] = copy_sep(operator, str, i);
		while (check_operator(str, i, operator) == 1 && str[i])
			i++;
		word++;
	}
	split[word] = NULL;
	return (split);
}
