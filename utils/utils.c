/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:09:22 by smarty            #+#    #+#             */
/*   Updated: 2024/06/08 22:13:11 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    get_env(t_data *data, char **env)
{
	int i;
	int y;

	i = 0;
	while(env[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while(env[++i])
	{
		y = 0;
		while(env[i][y])
			y++;
		data->env[i] = malloc(y + 1);
		y = -1;
		while(env[i][++y])
			data->env[i][y] = env[i][y];
		data->env[i][y] = 0;
	}
	data->env[i] = NULL;
}


int ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while(s2[++i])
	{
		if (s1[i] != s2[i])
			return (0);
	}
	return (1);
}

int ft_strmcmp(char *s1, char *s2, int y)
{
	int	i;

	i = -1;
	while(s2[++i] && i < y)
	{
		if (s1[i] != s2[i])
			return (0);
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
char	*ft_strjoin(char *s1, char *s2, int z, int y)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	i = (ft_strlen(s1) + ft_strlen(s2));
	j = -1;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	while (s1[++j])
		str[j] = s1[j];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = 0;
	if (z == 1)
		free (s1);
	if (y == 1)
		free (s2);
	return (str);
}

char	*find_var(char **env, char *var)
{
	char	*str;
	int		i;
	
	var = ft_strjoin(var, "=", 1, 0);
	i = 0;
	
	while (env[i])
	{
		if (ft_strstr(env[i], var))
			break;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	str = ft_strstr(env[i], var);
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
	while (ft_strstr(env[i], "PATH=") == 0)
		i++;
	env_path = ft_strstr(env[i], "PATH=");
	path = ft_split(env_path, ':');
	return (path);
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
int nb_order(t_data *data)
{
	t_list *tmp;
	int i;

	i = 0;
	tmp = data->line_lst;
	while(tmp)
	{
		//printf("content = %s   type = %d\n", tmp->content, tmp->content_type);
		if (tmp && tmp->content_type == TYPE_ORDER)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void alloc_pid(t_data *data)
{
	int	i;
	int	nb;

	i = -1;
	nb = nb_order(data);
	data->childpid = malloc(sizeof(int) * nb);
	if (data->childpid == NULL)
		exit(EXIT_FAILURE);
	while (++i < nb)
		data->childpid[i] = -2;
}

int is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
