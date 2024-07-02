/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:24:25 by oliradet          #+#    #+#             */
/*   Updated: 2024/07/02 15:00:00 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/**
 * unset all variable specified
 * @param data
 * @param args the table of variable to unset
 */
void	ft_unset(t_data *data, char *args)
{
	int		i;
	int		y;
	int		size;
	char	**tab;

	tab = ft_split(args, ' ');
	size = ft_size_tab(tab);
	i = 0;
	while (i < size)
	{
		y = find_env(data, tab[i]);
		if (y != -1)
		{
			free(data->env[y]);
			while (data->env[y])
			{
				data->env[y] = data->env[y + 1];
				y++;
			}
		}
		i++;
	}
	free(tab);
}
