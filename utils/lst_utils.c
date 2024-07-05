/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:06:47 by smarty            #+#    #+#             */
/*   Updated: 2024/06/01 23:28:10 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*ft_lstprint(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (!tmp)
		return (0);
	while (tmp)
	{
		printf("%s -> type = %d\n", tmp->content, tmp->content_type);
		tmp = tmp->next;
	}
	printf("\n");
	return (0);
}

t_list	*lst_add(t_list *lst, char *data)
{
	t_list	*node;
	t_list	*tmp;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = ft_strdup(data);
	node->next = NULL;
	if (!lst)
		return (node);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (lst);
}

t_list	*lst_prev(t_list *lst, t_list *original)
{
	t_list	*tmp;

	tmp = original;
	if (ft_strcmp(tmp->content, lst->content))
		return (NULL);
	while (tmp->next != lst)
		tmp = tmp->next;
	return (tmp);
}

t_list	*next_order(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp && tmp->content_type != 0)
		tmp = tmp->next;
	return (tmp);
}

void	delete_space(t_list *lst)
{
	int		i;
	int		y;
	char	*tmp;

	i = 0;
	while (lst->content[i] == ' ')
		i++;
	tmp = ft_strdup_v2(&lst->content[i]);
	free(lst->content);
	i = 0;
	y = 0;
	while (tmp[i])
	{
		if (tmp[i] == ' ')
			y++;
		else
			y = 0;
		i++;
	}
	tmp[i - y] = 0;
	lst->content = ft_strdup(tmp);
}
