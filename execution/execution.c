/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:41:59 by smarty            #+#    #+#             */
/*   Updated: 2024/07/10 16:15:48 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_data *data, t_list *lst)
{
	int		i;
	char	**cmd;
	char	**path;

	cmd = ft_split_arg(lst->content, ' ');
	path = find_path(data->env);
	i = 0;
	while (path && path[i])
	{
		path[i] = build_arg_path(cmd, path, i);
		if (access(path[i], F_OK | X_OK) == 0)
		{
			if (execve(path[i], cmd, data->env) == -1)
			{
				free_exec(path, cmd, data);
				exit(2);
			}
			exit (0);
		}
		free(path[i]);
		i++;
	}
	is_not_found(data, cmd, path, i);
	exit (0);
}

int	check_built_in_3(t_data *data, t_list *lst)
{
	if (ft_strcmp("exit", lst->content) == 1)
	{
		lst->content = delete_quotes(lst->content);
		ft_exit(data);
		return (1);
	}
	else if (ft_strmcmp(lst->content, "pwd ", 4) == 1)
	{
		lst->content = delete_quotes(lst->content);
		ft_pwd();
		return (1);
	}
	return (0);
}

int	check_built_in_2(t_data *data, t_list *lst)
{
	if (ft_strmcmp(lst->content, "export", 6) == 1)
	{
		lst->content = delete_quotes(lst->content);
		if (lst->content[6] == '\0')
			data->return_value = export_env(data, NULL);
		else if (lst->content[6] == ' ')
			data->return_value = export_env(data, &lst->content[7]);
		return (1);
	}
	else if (ft_strmcmp(lst->content, "unset ", 6) == 1)
	{
		lst->content = delete_quotes(lst->content);
		data->return_value = ft_unset(data, &lst->content[6]);
		return (1);
	}
	else if (ft_strcmp("env", lst->content) == 1)
	{
		data->return_value = ft_env(data);
		return (1);
	}
	return (check_built_in_3(data, lst));
}

int	check_built_in(t_data *data, t_list *lst)
{
	if (ft_strmcmp(lst->content, "echo -n ", 8) == 1)
	{
		lst->content = delete_quotes(lst->content);
		data->return_value = echo(&lst->content[8], 1);
		return (1);
	}
	else if (ft_strmcmp(lst->content, "echo ", 5) == 1
		&& ft_strmcmp(lst->content, "echo -", 6) == 0)
	{
		lst->content = delete_quotes(lst->content);
		data->return_value = echo(&lst->content[5], 0);
		return (1);
	}
	else if (ft_strmcmp(lst->content, "cd", 2) == 1)
	{
		lst->content = delete_quotes(lst->content);
		if (ft_strlen(&lst->content[0]) <= 3)
			data->return_value = ft_cd(data, value_env(
						data->env[get_env_index(data, "HOME=")]) + 1);
		else
			data->return_value = ft_cd(data, &lst->content[3]);
		return (1);
	}
	return (check_built_in_2(data, lst));
}

void	fork_order(t_data *data, t_list *lst)
{
	pid_t	pid;
	int		i;

	if (check_built_in(data, lst) == 1)
		return ;
	pid = fork();
	i = 0;
	if (pid == -1)
	{
		perror_process(data, "fork");
		return ;
	}
	else if (pid == 0)
	{
		execute(data, lst);
	}
	else
	{
		while (data->childpid[i] != -2)
			i++;
		data->childpid[i] = pid;
	}
}
