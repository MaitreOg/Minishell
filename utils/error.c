/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:24:35 by smarty            #+#    #+#             */
/*   Updated: 2024/06/07 19:53:56 by smarty           ###   ########.fr       */
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
    result = ft_strjoin("minishell: syntaxe error near ", error, 0, 0);
    if (lst->next == NULL)
        result = ft_strjoin(result, "'newline'", 1, 0);
    else if (lst->content_type == 5)
        result = ft_strjoin(result, lst->content, 1, 0);
    else
        result = ft_strjoin(result, lst->next->content, 1, 0);
    printf("%s\n", result);
    free (result);
    free_all(data);
    data->in_progress = 0;
}
void order_not_found(t_data *data, char *order)
{
    char *result;
    result = ft_strjoin("minishell: ", order, 0, 0);
    result = ft_strjoin(result, ": command not found", 1, 0);
    printf("%s\n", result);
    free (result);
    free_all(data);
    data->in_progress = 0;
}