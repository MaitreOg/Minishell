/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 00:18:35 by smarty            #+#    #+#             */
/*   Updated: 2023/10/26 00:43:18 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_function(int fd, char *stash)
{
	int		newl;
	int		value_read;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	newl = -1;
	value_read = 1;
	while (newl == -1 && value_read > 0)
	{
		value_read = read(fd, buffer, BUFFER_SIZE);
		if (value_read < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[value_read] = 0;
		newl = check_newl(buffer, value_read);
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*find_str(char *stash)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (stash[len] != '\n' && stash[len])
		len++;
	if (len == 0 && !stash[len])
		return (NULL);
	len++;
	str = malloc(len + 1);
	while (i < len)
	{
		str[i] = stash[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*next_line(char *stash)
{
	int		i;
	int		y;
	char	*str;

	i = 0;
	y = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	str = (char *)malloc(ft_strlen(stash) - i + 1);
	i++;
	while (stash[i])
	{
		str[y] = stash[i];
		y++;
		i++;
	}
	str[y] = 0;
	free(stash);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stash[4096];
	char		*str;

	if (!stash[fd])
	{
		stash[fd] = malloc(1);
		*stash[fd] = '\0';
	}
	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_function(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	str = find_str(stash[fd]);
	stash[fd] = next_line(stash[fd]);
	return (str);
}
