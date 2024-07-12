/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:16:31 by smarty            #+#    #+#             */
/*   Updated: 2024/06/01 23:23:28 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*is_interogation(t_data *data, char *str, char *var)
{
	int	i;

	i = 0;
	while (str[i] != '$')
		i++;
	str[i] = 0;
	free (var);
	var = ft_itoa(data->return_value);
	var = ft_strjoin(var, &str[i + 2], 1, 0);
	str = ft_strjoin(str, var, 1, 1);
	return (str);
}
int cv(t_data *data, char *str, char *backup, int y)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_strdup_v2(&str[1]);
	while  (var[i] != ' ' && is_verif_quotes(backup, i + y) == 0
				&& var[i] != '"' && var[i] != '\'' && var[i] && var[i] != '$')
			i++;
	var = ft_strjoin(var, "=", 1, 0);
	i = 0;
	while (data->env[i])
	{
		if (ft_strstr(data->env[i], var))
		{
			free (var);
			return (1);
		}
		i++;
	}
	free (var);
	return (0);
}

char	*is_var(t_data *data, char *str, char *var)
{
	int	i;
	int	y;

	i = 0;
	y = 1;
	while (str[i])
	{
		if (str[i] == '$' && cv(data, &str[i], str, i) == 1)
			break ;
		i++;
	}
	var = find_var(data->env, var);
	while (str[i + y] != ' ' && is_verif_quotes(str, i + y) == 0
		&& str[i + y] != '"' && str[i + y] != '\'' && str[i + y] && str[i + y] != '$')
		y++;
	var = ft_strjoin(var, &str[i + y], 0, 0);
	str[i] = 0;
	str = ft_strjoin(str, var, 1, 1);
	return (str);
}

char	*replace_var(t_data *data, char *str, int i, int y)
{
	char	*var;

	while (str[++i])
	{
		y = 1;
		if (str[i] == '$' && is_verif_quotes(str, i + y) == 0 && cv(data, &str[i], str, i) == 1)
		{
			while (str[i + y] != ' ' && is_verif_quotes(str, i + y) == 0
				&& str[i + y] != '"' && str[i + y] != '\'' && str[i + y] && str[i + y] != '$')
				y++;
			var = malloc (y + 1);
			y = 0;
			i++;
			while (str[i] != ' ' && is_verif_quotes(str, i) == 0
				&& str[i] != '"' && str[i] != '\'' && str[i] && str[i] != '$')
				var[y++] = str[i++];
			var[y] = 0;
			if (ft_strcmp("?", var) == 1)
				str = is_interogation(data, str, var);
			else
				str = is_var(data, str, var);
			//i = 0;
		}
	}
	return (str);
}
