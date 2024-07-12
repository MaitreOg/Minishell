/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:15:00 by oliradet          #+#    #+#             */
/*   Updated: 2024/07/05 14:15:00 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_var(char **env, char *var)
{
	char	*str;
	int		i;
	char	*not_exist;

	not_exist = ft_strjoin("$", var, 0, 0);
	var = ft_strjoin(var, "=", 1, 0);
	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], var))
			break ;
		i++;
	}
	if (env[i] == NULL)
	{
		printf("env not found\n");
		return (not_exist);
	}
	str = ft_strstr(env[i], var);
	free(not_exist);
	free (var);
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*d;

	i = 0;
	d = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!d)
		return (NULL);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = 0;
	free(s);
	return (d);
}

char	*ft_strdup_v2(char *s)
{
	int		i;
	char	*d;

	i = 0;
	d = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!d)
		return (NULL);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = 0;
	return (d);
}

char	**find_path(char **env)
{
	char	*env_path;
	char	**path;
	int		i;

	i = 0;
	while (env[i] && ft_strstr(env[i], "PATH=") == 0)
	{
		i++;
	}
	if (env[i] == NULL)
	{
		return (NULL);
	}
	env_path = ft_strstr(env[i], "PATH=");
	path = ft_split(env_path, ':');
	return (path);
}
