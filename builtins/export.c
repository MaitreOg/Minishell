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

void	print_sorted_env(t_data *data)
{
	char	**env;
	char	*tmp;
	int		i;
	int		j;

	env = ft_copy_tab(data->env);
	i = -1;
	while (env[++i])
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
	}
	i = -1;
	while (env[++i])
		printf("declare -x %s\n", env[i]);
	free_tab(env);
}

int	ft_strlen_special(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	return (i);
}

int	export_env(t_data *data, char *str)
{
	char	*value;
	int		i;

	if (str == NULL)
		return (print_sorted_env(data), 0);
	if (!valid_env_name_export(str))
		return (printf("export: `%s': not a valid identifier\n", str), -1);
	i = -1;
	value = value_env(str);
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], str, ft_strlen_special(str)) == 0)
		{
			if (ft_strcmp(data->env[i], str))
				printf("export: `%s': already in the env\n", str);
			edit_env(data, str, value);
			return (1);
		}
	}
	data->env = ft_realloc_tab(data->env, str);
	data->keys_env[i] = 0;
	if (value_env(str))
		data->keys_env[i] = 1;
	return (0);
}
