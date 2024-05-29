/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:41:59 by smarty            #+#    #+#             */
/*   Updated: 2024/05/29 17:12:13 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//coupure apres l exec a determiner pourquoi?
void execute(t_data *data, t_list *lst)
{
	int		i;
	char	**cmd;
	char	**path;

	cmd = ft_split(lst->content, ' ');
	path = find_path(data->env);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd[0]);
		if (access(path[i], F_OK | X_OK) == 0)
		{
			if (execve(path[i], cmd, data->env) == -1)
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
