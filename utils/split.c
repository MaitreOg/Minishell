/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:31:52 by smarty            #+#    #+#             */
/*   Updated: 2024/06/01 22:05:26 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_word(char *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (s[0] != c && s[0])
		nb++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			nb++;
		i++;
	}
	return (nb);
}

char	**cpyword(char **str, char *s, char c)
{
	int	i;
	int	y;
	int	word;

	i = 0;
	y = 0;
	word = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		while (s[i + y] != c && s[i + y])
			y++;
		str[word] = (char *)malloc (sizeof(char) * y + 1);
		y = 0;
		while (s[i] != c && s[i])
			str[word][y++] = s[i++];
		str[word][y] = '\0';
		y = 0;
		while ((s[i] == c || s[i] == ' ') && s[i])
			i++;
		word++;
	}
	str[word] = NULL;
	return (str);
}

char	**ft_split(char *str, char c)
{
	int		nb;
	char	**ss;

	nb = count_word(str, c);
	ss = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!ss)
		return (NULL);
	return (cpyword(ss, str, c));
}

int check_operator(char *str, int y, char *operator)
{
	int i;

	i = -1;
	while(operator[++i])
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
		if (check_operator(str, i, operator) == 1 && ((check_operator(str, (i + 1), operator) == 0 && str[i + 1]) || str[i + 1] == 0))
			nb += 1;
		if (check_operator(str, i, operator) == 0 && ((check_operator(str, (i + 1), operator) == 1 && str[i + 1]) || str[i + 1] == 0))
			nb += 1;
		i++;
	}
	return (nb);
}

char *copy_word(char *operator, char *str, int i)
{
	int y;
	char *split;

	y = 0;
	while (check_operator(str, (i + y), operator) == 0 && str[i + y])
		y++;
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


char **ft_split2(char *str, char*operator)
{
	int nb;
	int i;
	int y;
	int word;
	char **split;

	nb = count_word2(str, operator);
	split = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!split)
		return (NULL);
	word = 0;
	i = 0;
	while (str[i])
	{
		y = 0;
		while (check_operator(str, (i + y), operator) == 0 && str[i + y])
			y++;
		if (y > 0)
		{
			split[word] = (char *)malloc (sizeof(char) * (y + 1));
			y = 0;
   			while (check_operator(str, i, operator) == 0 && str[i])
			{
				split[word][y] = str[i];
				y++;
				i++;
			}
			split[word][y] = '\0'; 
			word++;
		}
		y = 0;
		if (str[i] == 0)
		{
			split[word] = NULL;
			return (split);
		}
		while (check_operator(str, (i + y), operator) == 1 && str[i + y])
			y++;
		split[word] = (char *)malloc (sizeof(char) * (y + 1));
		y = 0;
		while (check_operator(str, i, operator) == 1 && str[i])
		{
			split[word][y] = str[i];
			y++;
			i++;
		}
		split[word][y] = 0;
		while ( str[i] == ' ')
			i++;
		word++;;
	}
	split[word] = NULL;
	return 	(split);
}