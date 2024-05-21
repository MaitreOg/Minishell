/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:47:43 by smarty            #+#    #+#             */
/*   Updated: 2024/04/04 21:08:29 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    minishell(t_data *data)
{
	while (1)
	{
		data->line = readline("\033[0;35mminishell \033[0m ");
		if (data->line)
			add_history(data->line);
		data->line = replace_var(data, data->line);
		line_to_token(data);
		if (ft_strcmp(data->line, "exit"))
			return;
	}
}