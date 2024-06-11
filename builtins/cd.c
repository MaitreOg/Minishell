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
 * @return 0 success \n -1 error
 */
int	ft_cd(t_data *data, char *str)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (chdir(str) == -1)
	{
		printf("cd: %s: No such file or directory\n", str);
		free(pwd);
		return (-1);
	}
	edit_env(data, "PWD=", getcwd(NULL, 0));
	edit_env(data, "OLDPWD=", pwd);
	free(pwd);
	return (0);
}