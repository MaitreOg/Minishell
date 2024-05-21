/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:16:31 by smarty            #+#    #+#             */
/*   Updated: 2024/04/04 21:08:33 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *replace_var(t_data *data, char *str)
{
	int i;
	int y;
	char   *var;

	i = -1;
	while(data->line[++i])
	{
		y = 1;
		if (data->line[i] == '$' && is_verif_quotes(data->line, i) == 0)
		{
			while(data->line[i + y] != ' ' && data->line[i + y])
				y++;
			var = malloc (y + 1);
			y = 0;
			i++;
			while(data->line[i] != ' ' && data->line[i])
			{
				var[y] = data->line[i];
				y++; 
				i++;
			}
			var[y] = 0;
			var = find_var(data->env, var);
			i = 0;
			y = 0;
			while (data->line[i] != '$')
				i++;
			while (data->line[i + y] != ' ' && data->line[i + y])
				y++;
			var = ft_strjoin(var, &data->line[i + y]);
			data->line[i] = 0;
			data->line = ft_strjoin(data->line, var);
			printf("line = %s\n", data->line);
		}
	}
	return (data->line);

}
