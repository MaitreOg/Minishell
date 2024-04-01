/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:29:14 by smarty            #+#    #+#             */
/*   Updated: 2024/04/02 01:24:39 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    line_to_token(t_data *data)
{
    char **tab_pipe;
    char ***tab_redirection;
    int i;
    int y;

    i = 0;
    tab_pipe = ft_split2(data->line, "|");
    while(tab_pipe[i])
        i++;
    tab_redirection = malloc(sizeof(char **) *  (i + 1));
    i = -1;
    while(tab_pipe[++i])
        tab_redirection[i] = ft_split2(tab_pipe[i], "><");
    tab_redirection[i] = NULL;
    i = -1;
    while(tab_redirection[++i])
    {
        y = -1;
        while(tab_redirection[i][++y])
            printf("i : %d y : %d string :%s\n", i, y, tab_redirection[i][y]);
    }
}