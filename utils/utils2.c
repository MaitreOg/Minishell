/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:51:35 by oliradet          #+#    #+#             */
/*   Updated: 2024/07/09 20:51:35 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free (path);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free (cmd);
}

int	nb_order(t_data *data)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = data->line_lst;
	while (tmp)
	{
		if (tmp->content_type == TYPE_ORDER)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	alloc_pid(t_data *data)
{
	int	i;
	int	nb;

	i = -1;
	nb = nb_order(data);
	data->childpid = malloc(sizeof(int) * nb);
	if (data->childpid == NULL)
		exit(EXIT_FAILURE);
	while (++i < nb)
		data->childpid[i] = -2;
}

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
