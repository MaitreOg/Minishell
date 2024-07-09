/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:29:43 by oliradet          #+#    #+#             */
/*   Updated: 2024/07/02 22:29:43 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit(t_data *data)
{
	int	i;
//	int value;
//
//	value = ft_atoi(value_env(data->env[get_env_index(data, "SHLVL=")]) + 1);

	i = 0;
	shell_lvl_decr(data);

	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->keys_env);
	free_all(data);
	exit(0);
	return (0);
}
