/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:47:43 by smarty            #+#    #+#             */
/*   Updated: 2024/05/31 21:37:54 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    minishell(t_data *data)
{
	int stdout_backup;
	int stdin_backup;

	data->line_lst = NULL;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	while (1)
	{
		data->in_progress = 1;
		data->line_lst = NULL;
		data->o = 0;
		data->line = readline("\033[0;35mminishell \033[0m ");
		if (data->line[0])
		{
			add_history(data->line);
			line_to_token(data);
			if (ft_strcmp(data->line, "exit"))
				return;
			compute(data);
			free(data->line_lst);
			dup2(stdout_backup, STDOUT_FILENO);
			dup2(stdin_backup, STDIN_FILENO);
		}
	}
}