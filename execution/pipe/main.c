/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 03:39:18 by smarty            #+#    #+#             */
/*   Updated: 2023/12/17 19:31:54 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char **av, int ac)
{
	int		fdi;

	if (ft_strncmp("here_doc", av[1], 8) == 1 && ac < 6)
	{
		fdi = -2;
		perror("args");
	}
	else if (ft_strncmp("here_doc", av[1], 8) == 1)
		fdi = here_doc(av);
	else
		fdi = open(av[1], 0, 0666);
	if (fdi == -1)
		perror("fd");
	return (fdi);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	fdo;
	int	fdi;

	i = 0;
	fdi = open_file(av, ac);
	fdo = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	dup2(fdi, STDIN_FILENO);
	if (fdi == -1 || fdo == -1 || fdi == -2)
		exit(EXIT_FAILURE);
	if (ft_strncmp("here_doc", av[1], 8) == 1)
		i = 3;
	else if (ac > 5)
		i = 2;
	else
	{
		dup2(fdo, STDOUT_FILENO);
		create_childpid(av, env, 2);
		return (0);
	}
	while (i < ac -2)
		pipe_process(av, env, i++);
	dup2(fdo, STDOUT_FILENO);
	ex_cmd(av, env, i);
	return (0);
}
