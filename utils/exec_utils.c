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
