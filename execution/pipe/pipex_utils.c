/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:43:17 by smarty            #+#    #+#             */
/*   Updated: 2023/12/16 00:26:35 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (!to_find[i])
		return (str);
	while (str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j])
		{
			j++;
			if (!to_find[j])
				return (&str[i + j]);
		}
		return (0);
	}
	return (0);
}

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

/*int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}*/

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = (ft_strlen(s1) + ft_strlen(s2));
	j = 0;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	while (s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = 0;
	return (str);
}

char	**find_path(char **env)
{
	char	*env_path;
	char	**path;
	int		i;

	i = 0;
	while (ft_strstr(env[i], "PATH=") == 0)
		i++;
	env_path = ft_strstr(env[i], "PATH=");
	path = ft_split(env_path, ':');
	return (path);
}
