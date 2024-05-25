/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:06:47 by smarty            #+#    #+#             */
/*   Updated: 2024/05/25 23:18:29 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*ft_lstprint(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (!tmp)
		return 0;
	while (tmp)
	{
		printf("%s -> type = %d\n", tmp->content, tmp->content_type);
		tmp = tmp->next;
	}
	printf("\n");
	return 0;
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
	if (!lst->content)
		return (node);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (lst);
}

t_list	*lst_prev(t_list *lst, t_list *original)
{
    t_list *tmp;

    tmp = original;
    if (ft_strcmp(tmp->content, lst->content))
        return NULL;
    while (tmp->next != lst)
        tmp = tmp->next;
    return tmp;
}