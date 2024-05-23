/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:47:43 by smarty            #+#    #+#             */
/*   Updated: 2024/05/23 18:09:31 by smarty           ###   ########.fr       */
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
		line_to_token(data);
		if (ft_strcmp(data->line, "exit"))
			return;
	}
}