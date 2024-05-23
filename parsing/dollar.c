/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:16:31 by smarty            #+#    #+#             */
/*   Updated: 2024/05/23 18:09:22 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *replace_var(t_data *data, char *str)
{
	int i;
	int y;
	char   *var;

	i = -1;
	while(str[++i])
	{
		y = 1;
		if (str[i] == '$')
		{
			while(str[i + y] != ' ' && str[i + y])
				y++;
			var = malloc (y + 1);
			y = 0;
			i++;
			while(str[i] != ' ' && str[i])
			{
				var[y] = str[i];
				y++; 
				i++;
			}
			var[y] = 0;
			var = find_var(data->env, var);
			i = 0;
			y = 0;
			while (str[i] != '$')
				i++;
			while (str[i + y] != ' ' && str[i + y])
				y++;
			var = ft_strjoin(var, &str[i + y]);
			str[i] = 0;
			str = ft_strjoin(str, var);
		}
	}
	return (str);
}

