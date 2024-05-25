/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:35:51 by smarty            #+#    #+#             */
/*   Updated: 2023/12/16 00:32:11 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ex_cmd1(char **av, char **env, int y)
{
	int		i;
	char	**cmd1;
	char	**path;

	cmd1 = ft_split(av[y], ' ');
	path = find_path(env);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd1[0]);
		if (access(path[i], F_OK | X_OK) == 0)
		{
			if (execve(path[i], cmd1, env) == -1)
			{
				free_path(path);
				free_cmd(cmd1);
				perror("error cmd1");
			}
			break ;
		}
		free(path[i]);
		i++;
	}
}

void	ex_cmd2(char **av, char **env, int y)
{
	int		i;
	char	**cmd2;
	char	**path;

	cmd2 = ft_split(av[y + 1], ' ');
	path = find_path(env);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd2[0]);
		if (access(path[i], F_OK | X_OK) == 0)
		{
			if (execve(path[i], cmd2, env) == -1)
			{
				free_path(path);
				free_cmd(cmd2);
				perror("error cmd2");
			}
			break ;
		}
		free(path[i]);
		i++;
	}
}

void	create_childpid(char **av, char **env, int y)
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
	else if (childpid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ex_cmd2(av, env, y);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ex_cmd1(av, env, y);
	}
}

/*int	main(int ac, char **av, char **env)
{
	int		fdi;
	int		fdo;
	int		i;

	i = 2;
	fdi = open(av[1], 0, 0666);
	fdo = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fdo == -1 || fdi == -1)
		perror("fd");
	dup2(fdi, STDIN_FILENO);
	dup2(fdo, STDOUT_FILENO);
	close(fdi);
	close(fdo);
	create_childpid(av, env, i);
	return (0);
}*/
