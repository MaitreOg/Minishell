/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:47:43 by smarty            #+#    #+#             */
/*   Updated: 2024/05/30 22:22:52 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    minishell(t_data *data)
{
	int stdout_backup;
	int stdin_backup;

	data->line_lst = NULL;
	while (1)
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
		data->line_lst = NULL;
		data->o = 0;
		data->line = readline("\033[0;35mminishell \033[0m ");
		if (data->line[0])
		{
			add_history(data->line);
			line_to_token(data);
			if (ft_strcmp(data->line, "exit"))
			{
				return;
			}
			compute(data);
			free(data->line_lst);
			if (dup2(stdout_backup, STDOUT_FILENO) == -1)
			{
        		perror("dup2");
        		close(stdout_backup);
        		exit(EXIT_FAILURE);
			}
			if (dup2(stdin_backup, STDIN_FILENO) == -1)
			{
        		perror("dup2");
        		close(stdout_backup);
        		exit(EXIT_FAILURE);
			}
		}
	}
}