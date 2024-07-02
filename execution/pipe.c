/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:54:37 by smarty            #+#    #+#             */
/*   Updated: 2024/06/08 21:45:26 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
void	child_pipes(int fd[2], t_data *data)
{
    close(fd[0]);
    if (data->o == 0)
	    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
}

void	pipes(t_data *data, t_list *order, int i)
{
	pid_t	childpid;
	int		fd[2];
	int 	status;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	childpid = fork();
	if (childpid == -1)
		return (perror_process(data, "fork"));
	if (childpid == 0)
	{
		child_pipes(fd, data);
		execute(data, order);
	}
	else
	{
        close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
		while(data->childpid[i] != -2)
			i++;
		data->childpid[i] = childpid;
		data->return_value = WEXITSTATUS(status);
	}
}
