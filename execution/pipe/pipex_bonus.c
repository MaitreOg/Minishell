/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 21:45:54 by smarty            #+#    #+#             */
/*   Updated: 2023/12/16 00:31:37 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ex_cmd(char **av, char **env, int y)
{
	int		i;
	char	**cmd;
	char	**path;

	cmd = ft_split(av[y], ' ');
	path = find_path(env);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd[0]);
		if (access(path[i], F_OK | X_OK) == 0)
		{
			if (execve(path[i], cmd, env) == -1)
			{
				free_path(path);
				free_cmd(cmd);
				perror("error cmd");
			}
			break ;
		}
		free(path[i]);
		i++;
	}
}

void	pipe_process(char **av, char **env, int i)
{
	pid_t	childpid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	childpid = fork();
	if (childpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (childpid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ex_cmd(av, env, i);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(childpid, NULL, 0);
	}
}

void	create_file_doc(char **av, int *fd)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(av[2], "\n");
	write(STDIN_FILENO, "pipex: here_doc> ", 17);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(limiter, line, ft_strlen(limiter)))
		{
			get_next_line(-1);
			free(limiter);
			free(line);
			close(*fd);
			exit(0);
		}
		write(*fd, line, ft_strlen(line));
		free(line);
		write(STDIN_FILENO, "pipex: here_doc> ", 17);
		line = get_next_line(STDIN_FILENO);
	}
}

int	here_doc(char **av)
{
	pid_t	childpid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	childpid = fork();
	if (childpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (childpid == 0)
	{
		waitpid(childpid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		create_file_doc(av, &fd[1]);
	}
	return (STDIN_FILENO);
}
