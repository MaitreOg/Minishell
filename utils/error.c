/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:24:35 by smarty            #+#    #+#             */
/*   Updated: 2024/06/01 22:47:55 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void perror_process(t_data *data, char *error)
{
    perror(error);
    free_all(data);
    data->in_progress = 0;
}

void redirect_error(t_data *data, char *error, t_list *lst)
{
    char *result;
    if (lst->next == NULL)
        result = ft_strjoin(error, "'newline'", 0, 0);
    else if (lst->content_type == 5)
        result = ft_strjoin(error, lst->content, 0, 0);
    else
        result = ft_strjoin(error, lst->next->content, 0, 0);
    printf("syntax error near\n%s\n", result);
    free_all(data);
    data->in_progress = 0;
}
void order_not_found(t_data *data, char *order)
{
    char *result;

    result = ft_strjoin(order, ": command not found", 0, 0);
    printf("%s\n", result);
    free_all(data);
    data->in_progress = 0;
}