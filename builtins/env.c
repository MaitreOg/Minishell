/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:20:53 by oliradet          #+#    #+#             */
/*   Updated: 2024/05/25 02:20:53 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * print the env
 * @param data the struct for get the emv variable
 */
int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (data->keys_env[i] == 1)
			printf("%s\n", data->env[i]);
		i++;
	}
	return (0);
}
