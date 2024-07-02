/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:24:11 by oliradet          #+#    #+#             */
/*   Updated: 2024/07/02 21:06:12 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * echo :)
 * @param str the string to print
 * @param arg arg n or not : \n 0 : no arg \n 1 : -n
 */
int	echo(char *str, int arg)
{
	if (!str)
	{
		if (arg == 0)
			printf("%s\n", str);
		else
			printf("%s", str);
		return (0);
	}
	return (2);
}
