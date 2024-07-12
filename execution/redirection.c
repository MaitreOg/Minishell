/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:41:49 by smarty            #+#    #+#             */
/*   Updated: 2024/07/11 16:43:14 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrlc_heredoc(int signum)
{
	(void) signum;
	rl_replace_line("\0", 0);
	rl_replace_line("\0", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	exit(1);
}

void	redirect_input(t_data *data, t_list *lst)
{
	int	fd;

	fd = open(lst->content, O_RDONLY);
	if (fd == -1)
	{
		perror_process(data, lst->content);
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror_process(data, "dup2");
		close(fd);
		return ;
	}
	close(fd);
}

void	create_file_doc(t_data *data, t_list *lst, int *fd)
{
	char	*line;
	char	*limiter;

	signal(SIGINT, ctrlc_heredoc);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	limiter = ft_strjoin(lst->content, "\n", 0, 0);
	write(2, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	(void) data;
	while (line)
	{
		if (ft_strcmp(limiter, line))
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
		write(2, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd[1]);
	free(limiter);
	free(line);
	get_next_line(-1);
	exit(0);
}

void	limiter(t_data *data, t_list *lst)
{
	pid_t	childpid;
	int		fd[2];
	int		backup;

	backup = dup(STDOUT_FILENO);
	dup2(data->stdin, STDIN_FILENO);
	if (pipe(fd) == -1)
		return (perror_process(data, "pipe"));
	childpid = fork();
	if (childpid == -1)
	{
		perror_process(data, "fork");
		return ;
	}
	if (childpid == 0)
		create_file_doc(data, lst, fd);
	else
	{
		close(fd[1]);
		waitpid(childpid, NULL, 0);
		dup2(backup, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	redirect_output(t_data *data, t_list *lst, int append)
{
	int	fd;
	int	flags;

	data->o = 1;
	if (append == 1)
		flags = O_RDWR | O_CREAT | O_APPEND;
	else
		flags = O_RDWR | O_CREAT | O_TRUNC;
	fd = open(lst->content, flags, 0644);
	if (fd == -1)
	{
		perror_process(data, lst->content);
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror_process(data, "dup2");
		close(fd);
		return ;
	}
	close(fd);
}
