/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:41:49 by smarty            #+#    #+#             */
/*   Updated: 2024/05/29 17:12:19 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    redirect_input(t_data *data, t_list *lst)
{
    int fd;
    fd = open(lst->next->next->content, O_WRONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(STDIN_FILENO, fd);
	close(fd);
}

void    limiter(t_data *data, t_list *lst)
{
	
}

void    redirect_output(t_data *data, t_list *lst, int append)
{
    int fd;
	int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
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
