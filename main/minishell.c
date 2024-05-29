/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:47:43 by smarty            #+#    #+#             */
/*   Updated: 2024/05/29 12:58:22 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    minishell(t_data *data)
{
	data->line_lst = NULL;
	while (1)
	{
		data->line_lst = NULL;
		data->line = readline("\033[0;35mminishell \033[0m ");
		if (data->line)
		{
			add_history(data->line);
		}
		line_to_token(data);
		if (ft_strcmp(data->line, "exit"))
		{
			return;
		}
		compute(data);
		free(data->line_lst);
	}
}