/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:41:59 by smarty            #+#    #+#             */
/*   Updated: 2024/06/08 21:56:34 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_exec(char **path, char **cmd, t_data *data)
{
	free_path(path);
	free_cmd(cmd);
	perror_process(data, "error cmd");
}
char *build_arg_path(char **cmd, char **path, int i)
{
	if (cmd[0][0] != '/')
	{
		path[i] = ft_strjoin(path[i], "/", 1, 0);
		path[i] = ft_strjoin(path[i], cmd[0], 1, 0);
	}
	else
		path[i] = ft_strdup_v2(cmd[0]);
	return (path[i]);
}

void is_not_found(t_data * data, char **cmd, char **path, int i)
{
	if (path[i] == NULL)
	{
		free(path);
		order_not_found(data, cmd[0]);
		free_tab(cmd);
		exit(127);
	}
}
void execute(t_data *data, t_list *lst)
{
	int		i;
	char	**cmd;
	char	**path;

	cmd = ft_split_arg(lst->content, ' ');
	path = find_path(data->env);
	i = 0;
	while (path[i])
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
int check_built_in_2(t_data *data, t_list *lst)
{
	if (ft_strmcmp(lst->content, "export", 6) == 1)
	{
		lst->content = delete_quotes(lst->content);
		export_env(data, &lst->content[7]);
		return (1);
	}
	else if (ft_strmcmp(lst->content, "unset", 5) == 1)
	{
		lst->content = delete_quotes(lst->content);
		ft_unset(data, &lst->content[6]);
		return (1);
	}
	else if (ft_strcmp(lst->content, "env") == 1)
	{
		ft_env(data);
		return (1);
	}
	else if (ft_strcmp(lst->content, "exit") == 1)
	{
		lst->content = delete_quotes(lst->content);
		ft_exit(data);
		return (1);
	}
	return (0);
}

int	check_built_in(t_data *data, t_list *lst)
{
	if (ft_strmcmp(lst->content, "echo -n", 7) == 1)
	{
		lst->content = delete_quotes(lst->content);
		echo(&lst->content[8], 1);
		return (1);
	}
	else if (ft_strmcmp(lst->content, "echo", 4) == 1)
	{
		lst->content = delete_quotes(lst->content);
		echo(&lst->content[5], 0);
		return (1);
	}
	else if (ft_strmcmp(lst->content, "cd", 2) == 1)
	{
		lst->content = delete_quotes(lst->content);
		ft_cd(data, &lst->content[3]);
		return (1);
	}
	else if (ft_strcmp(lst->content, "pwd") == 1)
	{
		lst->content = delete_quotes(lst->content);
		ft_pwd();
		return (1);
	}
	return (check_built_in_2(data, lst));
}


void fork_order(t_data *data, t_list *lst)
{
	if (check_built_in(data, lst) == 1)
		return ;
	pid_t pid = fork();
	int status;
	int i;

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
		while(data->childpid[i] != -2)
			i++;
		data->childpid[i] = pid;
		data->return_value = WEXITSTATUS(status);
	}
}
