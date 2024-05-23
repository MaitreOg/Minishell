/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:24:11 by oliradet          #+#    #+#             */
/*   Updated: 2024/05/23 17:24:11 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * echo :)
 * @param str the string to print
 * @param arg arg n or not : \n 0 : no arg \n 1 : -n
 */
void echo(char *str, int arg)
{
	if (arg == 0)
		printf("%s\n", str);
	else
		printf("%s", str);
}