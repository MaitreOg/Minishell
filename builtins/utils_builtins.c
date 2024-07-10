/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:50:43 by oliradet          #+#    #+#             */
/*   Updated: 2024/07/09 05:48:21 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_env(t_data *data, char *name)
{
	int	i;
	int	y;

	i = 0;
	while (data->env[i])
	{
		y = 0;
		while (data->env[i][y] && data->env[i][y] != '=')
			y++;
		if (ft_strncmp(data->env[i], name, y) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	edit_env(t_data *data, char *name, char *value)
{
	char	*new_value;
	int		y;
	int		i;

	i = 0;
	while (data->env[i])
	{
		y = 0;
		while (data->env[i][y] && data->env[i][y] != '=')
			y++;
		if (ft_strncmp(data->env[i], name, y) == 0)
		{
			free(data->env[i]);
			new_value = malloc(ft_strlen(name) + ft_strlen(value) + 2);
			strcpy(new_value, name);
			data->env[i] = new_value;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	valid_env_name(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (0);
	i++;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
