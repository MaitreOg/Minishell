/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:31:52 by smarty            #+#    #+#             */
/*   Updated: 2024/06/01 23:29:20 by smarty           ###   ########.fr       */
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

int	count_word_arg(char *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (s[0] != c && s[0])
		nb++;
	while (s[i])
	{
		if (is_verif(s, i) == 0 && s[i] == c && s[i + 1] != c && s[i + 1])
			nb++;
		i++;
	}
	return (nb);
}

char	**cpyword_arg(char **str, char *s, char c, int i)
{
	int	y;
	int	word;

	i = 0;
	y = 0;
	word = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		while ((s[i + y] != c || is_verif(s, i + y) == 1) && s[i + y])
			y++;
		str[word] = (char *)malloc (sizeof(char) * y + 1);
		y = 0;
		while ((s[i] != c || is_verif(s, i) == 1) && s[i])
			str[word][y++] = s[i++];
		str[word][y] = '\0';
		y = 0;
		while ((s[i] == c || s[i] == ' ') && s[i])
			i++;
		str[word] = delete_quotes(str[word]);
		word++;
	}
	str[word] = NULL;
	return (str);
}
