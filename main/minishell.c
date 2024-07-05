/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:47:43 by smarty            #+#    #+#             */
/*   Updated: 2024/06/01 23:23:03 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    minishell(t_data *data, char **env)
{
	int stdout_backup;
	int stdin_backup;

	data->line_lst = NULL;
	data->stdin = dup(STDIN_FILENO);
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	get_env(data, env);
	data->childpid = NULL;
//	shell_lvl_incr(data);
//	shell_lvl_incr(data);
	while (1)
	{
		data->in_progress = 1;
		data->line_lst = NULL;
		data->o = 0;
		data->line = readline("\033[0;35mminishell \033[0m ");
		/*if (!data->line)
		{
			ft_exit(data);
		}*/
		if (ft_strcmp(data->line, "exit"))
		{
			free_tab(data->env);
			free(data->line);
			return ;
		}
		else if (is_only_space(data->line) == 1)
			free(data->line);
		else if (data->line[0] && is_only_space(data->line) == 0)
		{
			add_history(data->line);
			line_to_token(data);
			compute(data);
			dup2(stdout_backup, STDOUT_FILENO);
			dup2(stdin_backup, STDIN_FILENO);
		}

	}
}
