/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:41:59 by smarty            #+#    #+#             */
/*   Updated: 2024/06/01 22:32:19 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void execute(t_data *data, t_list *lst)
{
	int		i;
	char	**cmd;
	char	**path;

	cmd = ft_split(lst->content, ' ');
	path = find_path(data->env);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/", 1, 0);
		path[i] = ft_strjoin(path[i], cmd[0], 1, 0);
		if (access(path[i], F_OK | X_OK) == 0)
		{
			if (execve(path[i], cmd, data->env) == -1)
			{
				free_path(path);
				free_cmd(cmd);
				perror_process(data, "error cmd");
				return ;
			}
			break ;
		}
		free(path[i]);
		i++;
	}
	if (path[i] == NULL)
		order_not_found(data, cmd[0]);
	exit(1);
}

void fork_order(t_data *data, t_list *lst)
{

	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		perror_process(data, "fork");
		return ;
	}
	else if (pid == 0)
	{
		execute(data, lst);
	}
	else
	{
        waitpid(pid, &status, 0);
	}
}
