/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:41:49 by smarty            #+#    #+#             */
/*   Updated: 2024/05/29 19:38:19 by smarty           ###   ########.fr       */
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

void    limiter(t_data *data, t_list *lst)
{
	
}

void    redirect_output(t_data *data, t_list *lst, int append)
{
    int fd;
	int flags;

	data->o = 1;
	flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
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
