/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:55:36 by oliradet          #+#    #+#             */
/*   Updated: 2024/07/10 15:55:36 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_ispresent(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	nb;

	i = 0;
	neg = 1;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb * neg);
}

void	shell_lvl_decr(t_data *data)
{
	int	value;

	value = ft_atoi(value_env(data->env[get_env_index(data, "SHLVL=")]) + 1);
	if (value > 1)
	{
		value--;
		edit_env(data, "SHLVL=", ft_itoa(value));
	}
}

void	shell_lvl_incr(t_data *data)
{
	int	value;

	value = ft_atoi(value_env(data->env[get_env_index(data, "SHLVL=")]) + 1);
	value++;
	export_env(data, ft_strjoin("SHLVL=", ft_itoa(value), 0, 0));
}

int	env_has_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
