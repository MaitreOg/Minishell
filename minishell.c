/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:47:43 by smarty            #+#    #+#             */
/*   Updated: 2024/03/28 16:28:59 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    minishell(t_data *data)
{
	while (1)
	{
		data->line = readline("minishell :) ");
		line_to_token(data);
		if (ft_strcmp(data->line, "exit"))
			return;
	}
}