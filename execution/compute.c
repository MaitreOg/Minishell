/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:59:45 by smarty            #+#    #+#             */
/*   Updated: 2024/06/08 21:41:20 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void link_io(t_data *data,t_list *order, t_list *tmp)
{
	if (tmp->content_type == TYPE_PIPE)
	{
		data->execute = 1;
		pipes(data, order);
		return ;
	}
	if (tmp->next == NULL || (tmp->next->content_type > 0 && tmp->next->content_type < 6))
	{
		redirect_error(data, "unexpected token ", tmp);
		return;
	}
	else if (tmp->content_type == TYPE_LIMITER)
		limiter(data, tmp->next);
	else if (tmp->content_type == TYPE_ROUT)
		redirect_output(data, tmp->next, 0);
	else if (tmp->content_type == TYPE_ROUT_APP)
		redirect_output(data, tmp->next, 1);
	else if (tmp->content_type == TYPE_RIN)
		redirect_input(data, tmp->next);
}

void compute_operator(t_data *data, t_list *lst)
{
	t_list *tmp;
	t_list *order;

	order = lst;
	tmp = lst->next;
    
	while (data->in_progress == 1 && tmp && tmp->content_type != TYPE_ORDER)
	{
		if (tmp->content_type != TYPE_FILE)
			link_io(data, order, tmp);
		if (data->in_progress == 1)
			tmp = tmp->next;
	}
}
void backup_fd(t_data *data, int fdi, int fdo)
{
	dup2(fdo, STDOUT_FILENO);
	if (data->execute == 0)
		dup2(fdi, STDIN_FILENO);
	data->o = 0;
}
void compute(t_data *data)
{
	t_list *lst;
	int 	stdout_backup;
	int 	stdin_backup;
	int 	i;
	int 	status;

	i = -1;
	stdout_backup = dup(STDOUT_FILENO);
	stdin_backup = dup(STDIN_FILENO);
	alloc_pid(data);
	lst = data->line_lst;
	if (lst->content_type > 0 && lst->content_type < 5 && (lst->next == NULL || (lst->next->content_type > 0 && lst->next->content_type < 6)))
		redirect_error(data, "unexpected token ", lst);
	if (lst->content_type == 5)
		redirect_error(data, "unexpected token ", lst);
	while (lst && data->in_progress == 1)
	{
		data->fdo = stdout_backup;
		if(lst->content_type == TYPE_ORDER)
		{
			data->execute = 0;
			compute_operator(data, lst);
			if (data->execute == 0 && data->in_progress == 1)
				fork_order(data, lst);
			backup_fd(data, stdin_backup, stdout_backup);
		}
		if (data->in_progress == 1)
			lst = lst->next;
	}
	close(stdout_backup);
	close(stdin_backup);
	if (data->in_progress == 1)
	{
		while (++i < nb_order(data))
			waitpid(data->childpid[i], &status, 0);
		data->return_value = WEXITSTATUS(status);
		free_all(data);
	}
}
