#include "../include/minishell.h"

void	free_exec(char **path, char **cmd, t_data *data)
{
	free_path(path);
	free_cmd(cmd);
	perror_process(data, "error cmd");
}

char	*build_arg_path(char **cmd, char **path, int i)
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

void	is_not_found(t_data *data, char **cmd, char **path, int i)
{
	if (!path)
	{
		order_not_found(data, cmd[0]);
		free_tab(cmd);
		exit(127);
	}
	else if (path[i] == NULL)
	{
		free(path);
		order_not_found(data, cmd[0]);
		free_tab(cmd);
		exit(127);
	}
}

int	last_order(t_list *lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = lst;
	while (tmp)
	{
		if (tmp->content_type == 0)
			tmp2 = tmp;
		tmp = tmp->next;
	}
	if (ft_strmcmp(tmp2->content, "pwd", 3) == 1)
		return (0);
	if (ft_strmcmp(tmp2->content, "cd", 2) == 1)
		return (0);
	if (ft_strmcmp(tmp2->content, "env", 3) == 1)
		return (0);
	if (ft_strmcmp(tmp2->content, "export", 6) == 1)
		return (0);
	if (ft_strmcmp(tmp2->content, "unset", 5) == 1)
		return (0);
	if (ft_strmcmp(tmp2->content, "echo", 4) == 1)
		return (0);
	return (1);
}

char	*find_var2(char **env, char *var)
{
	char	*str;
	int		i;

	var = ft_strjoin(var, "=", 0, 0);
	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], var))
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	str = ft_strstr(env[i], var);
	free (var);
	return (str);
}
