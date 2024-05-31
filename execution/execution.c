/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:41:59 by smarty            #+#    #+#             */
/*   Updated: 2024/05/31 18:22:58 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//coupure apres l exec a determiner pourquoi?
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
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd[0]);
		if (access(path[i], F_OK | X_OK) == 0)
		{
			if (execve(path[i], cmd, data->env) == -1)
			{
				free_path(path);
				free_cmd(cmd);
				perror("error cmd");
				exit(EXIT_FAILURE);
			}
			break ;
		}
		free(path[i]);
		i++;
	}
	exit(1);
}

void fork_order(t_data *data, t_list *lst)
{

	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execute(data, lst);
	}
	else
	{
        waitpid(pid, &status, 0);
        g_exit_status = WEXITSTATUS(status);
	}
}
