/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:50:08 by smarty            #+#    #+#             */
/*   Updated: 2024/04/04 22:25:41 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void    pwd(t_data *data)
{
    int i;
    char *line;

    i = 0;
    while (ft_strstr(data->env[i], "PWD=") == 0)
        i++;
    line = ft_strstr(data->env[i], "PWD=");
    
    
}