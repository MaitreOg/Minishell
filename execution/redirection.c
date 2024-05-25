/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:41:49 by smarty            #+#    #+#             */
/*   Updated: 2024/05/25 23:24:02 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    redirect_output(t_data *data, t_list *lst)
{

}

void    redirect_input(t_data *data, t_list *lst)
{

}

void    limiter(t_data *data, t_list *lst)
{

}

void    redirect_output_a(t_data *data, t_list *lst)
{
    int fd;
    fd = open(lst->next->next->content, 0, 0666);
	if (fd == -1)
		perror("fd");
	dup2(STDOUT_FILENO, fd);
}
