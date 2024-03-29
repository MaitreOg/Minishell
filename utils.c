/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:09:22 by smarty            #+#    #+#             */
/*   Updated: 2024/03/28 14:31:51 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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