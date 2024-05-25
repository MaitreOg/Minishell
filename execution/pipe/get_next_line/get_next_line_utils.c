/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:54:44 by smarty            #+#    #+#             */
/*   Updated: 2023/12/15 23:56:38 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strlen_newl(char *stash)
{
	int	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	return (ft_strlen(stash) - i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = (ft_strlen(s1) + ft_strlen(s2));
	j = 0;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = 0;
	free(s1);
	return (str);
}

int	check_newl(char *stash, int value_read)
{
	int	i;
	int	result;

	i = 0;
	result = -1;
	if (!stash)
		return (0);
	if (value_read < BUFFER_SIZE)
		return (1);
	while (stash[i])
	{
		if (stash[i] == '\n')
			result = 1;
		i++;
	}
	return (result);
}
