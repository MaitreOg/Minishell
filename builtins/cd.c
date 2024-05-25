/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:29:07 by oliradet          #+#    #+#             */
/*   Updated: 2024/05/25 01:29:07 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * just an cd
 * @param str the path to go
 */
void	ft_cd(char *str)
{
	if (chdir(str) == -1)
		printf("cd: %s: No such file or directory\n", str);

}