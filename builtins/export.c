/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:35:28 by oliradet          #+#    #+#             */
/*   Updated: 2024/07/03 19:26:55 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_copy_tab(char **tab)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup_v2(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

void print_sorted_env(t_data *data)
{
	int i;
	int j;
	char *tmp;
	char **env;

	env= ft_copy_tab(data->env);
	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	free_tab(env);
}

int	export_env(t_data *data, char *str)
{
	char	*value;
	int		i;

	if (str == NULL)
	{
		print_sorted_env(data);
		return (0);
	}
	if (!valid_env_name_export(str))
	{
		printf("export: `%s': not a valid identifier\n", str);
		return (-1);
	}
	i = 0;
	value = value_env(str);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], str, ft_strlen(str)) == 0)//todo jusquau =
		{
			printf("export: `%s': already in the env\n", str);
			edit_env(data, str, value);
			return (1);
		}
		i++;
	}
	data->env = ft_realloc_tab(data->env, str);
	if (value_env(str))
		data->keys_env[i] = 1;
	else
		data->keys_env[i] = 0;
	return (0);
}
