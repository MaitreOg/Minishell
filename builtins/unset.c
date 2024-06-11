/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:24:25 by oliradet          #+#    #+#             */
/*   Updated: 2024/05/25 02:24:25 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * unset all variable specified
 * @param data
 * @param args the table of variable to unset
 */
void ft_unset(t_data *data, char **args)
{

	int i;
	int index;

	i= 0;
	while (args[i])
	{
		if (!valid_env_name(args[i]) || ft_ispresent(args[i], '='))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
			data->ret = 1;
		}
		else
		{
			index = get_env_index(data, args[i]);
			if (index != -1)
			{
				free(data->env[index]);
				while (data->env[index])
				{
					data->env[index] = data->env[index + 1];
					index++;
				}
			}
		}
	}
}