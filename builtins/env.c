/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:20:53 by oliradet          #+#    #+#             */
/*   Updated: 2024/05/25 02:20:53 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO TESTER ENV()
/**
 * print the env
 * @param data the struct for get the emv variable
 */
void env(t_data *data)
{
	printf("%s", *data->env);
}