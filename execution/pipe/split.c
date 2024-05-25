/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:56:44 by smarty            #+#    #+#             */
/*   Updated: 2023/11/30 14:54:31 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		while (s[i] == c && s[i])
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

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}
