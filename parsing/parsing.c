/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:29:14 by smarty            #+#    #+#             */
/*   Updated: 2024/06/08 22:09:49 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_type(t_list *lst, t_list *original)
{
	if (ft_strcmp("<", lst->content) == 1)
		lst->content_type = TYPE_RIN;
	else if (ft_strcmp("|", lst->content) == 1)
		lst->content_type = TYPE_PIPE;
	else if (ft_strcmp("<<", lst->content) == 1)
		lst->content_type = TYPE_LIMITER;
	else if (ft_strcmp(">", lst->content) == 1)
		lst->content_type = TYPE_ROUT;
	else if (ft_strcmp(">>", lst->content) == 1)
		lst->content_type = TYPE_ROUT_APP;
	else if (lst_prev(lst, original)
        && (lst_prev(lst, original)->content_type == TYPE_ROUT
			|| lst_prev(lst, original)->content_type == TYPE_ROUT_APP
			|| lst_prev(lst, original)->content_type == TYPE_RIN
			|| lst_prev(lst, original)->content_type == TYPE_LIMITER))
		lst->content_type = TYPE_FILE;
	else
		lst->content_type = TYPE_ORDER;
}

void	token_to_lst(char **tab, t_data *data)
{
	int	i;

	i = -1;
	data->line_lst = NULL;
	while (tab[++i])
	{
		data->line_lst = lst_add(data->line_lst, tab[i]);
	}
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
void	replace_path(t_data *data, t_list *lst)
{
	char *tmp;
	if (lst->content_type != 0)
		return;
	if (lst->content[0] == '.' && lst->content[1] == '/')
	{
		tmp = find_var2(data->env, "PWD");
		tmp = ft_strjoin(tmp, &lst->content[1], 0, 0);
		free (lst->content);
		lst->content = ft_strdup_v2(tmp);
	}
}
void	add_necessary(t_data *data)
{
	t_list	*tmp;
	char *absolute;
	
	tmp = data->line_lst;
	absolute = find_var2(data->env, "PWD");
	absolute = ft_strjoin(absolute, &tmp->content[1], 0, 0);
//	if (ft_strcmp(tmp->content, "./minishell") == 1 && tmp->next == NULL)
//		shell_lvl_incr(data);
//	else if (ft_strcmp(tmp->content, absolute) == 1 && tmp->next == NULL)
//		shell_lvl_incr(data);
	free (absolute);
	while (tmp)
	{
		add_type(tmp, data->line_lst);
		tmp->content = replace_var(data, tmp->content, -1);
		replace_path(data, tmp);
		delete_space(tmp);
		tmp = tmp->next;
	}
}

void	line_to_token(t_data *data)
{
	char	**tab;

	tab = ft_split2(data->line, "|<>");
	token_to_lst(tab, data);
	free(tab);
	add_necessary(data);
}
