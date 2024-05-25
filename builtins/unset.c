/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:24:25 by oliradet          #+#    #+#             */
/*   Updated: 2024/05/25 02:24:25 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//todo finish
/**
 * unset all variable specified
 * @param data
 * @param ...
 */
void unset(t_data *data, ...)
{
	va_list	arg;

	va_start(arg, data);
	while (arg)
	{
		printf("remove : %s", va_arg(arg, char *));
	}
}