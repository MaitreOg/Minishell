/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:35:28 by oliradet          #+#    #+#             */
/*   Updated: 2024/05/25 01:35:28 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	export_env(t_data *data, char *str)
{
	char	*value;
	int		i;

	if (!valid_env_name_export(str))
	{
		printf("export: `%s': not a valid identifier\n", str);
		return (-1);
	}
	i = 0;
	value = value_env(str);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], str, ft_strlen(str)) == 0)
		{
			printf("export: `%s': already in the env\n", str);
			edit_env(data, str, value);
			return (1);
		}
		i++;
	}
	data->env = ft_realloc_tab(data->env, str);
	return (0);
}
