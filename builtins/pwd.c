/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:25:18 by oliradet          #+#    #+#             */
/*   Updated: 2024/06/20 14:48:14 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * pwd
 */
void    ft_pwd()
{
	char *pwd;

	pwd = NULL;
	if (getcwd(NULL, 0) == NULL)
	{
		printf("zboub");
		return ;
	}
	else
		pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}