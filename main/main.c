/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:07:02 by smarty            #+#    #+#             */
/*   Updated: 2024/04/04 21:08:25 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int	i = 0;
	if (ac != 1 ||av[0][0] != '.')
		return(printf("please enter valid argument\n"));
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("alloc failes\n"));
	get_env(data, env);
	minishell(data);
	//free_all()
}