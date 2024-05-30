/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:41:49 by smarty            #+#    #+#             */
/*   Updated: 2024/05/31 01:18:38 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//probleme a regler : - rev < file > file    !ne fonctione pas! 
void    redirect_input(t_data *data, t_list *lst)
{
    int fd;
    fd = open(lst->content, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		printf("test\n");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
	close(fd);
}
void	create_file_doc(t_list *lst, int *fd)
{
	char	*line;
	char	*limiter;

	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	limiter = ft_strjoin(lst->content, "\n");
	write(2, "here_doc> ", 10);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strcmp(limiter, line))
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
		write(2, "here_doc> ", 10);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd[1]);
	get_next_line(-1);
	free(limiter);
	free(line);
	exit(g_exit_status);
}

void    limiter(t_data *data, t_list *lst)
{
	pid_t	childpid;
	int		fd[2];
	int status;

	if (pipe(fd) == -1)
	{
		perror("limiter");
		exit(EXIT_FAILURE);
	}
	childpid = fork();
	if (childpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (childpid == 0)
	{
		create_file_doc(lst, fd);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		waitpid(childpid, &status, 0);
        g_exit_status = WEXITSTATUS(status);
	}
}

void    redirect_output(t_data *data, t_list *lst, int append)
{
    int fd;
	int flags;

	data->o = 1;
	flags = O_RDWR | O_CREAT | (append ? O_APPEND : O_TRUNC);
    fd = open(lst->content, flags, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
	close(fd);
}
