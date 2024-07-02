/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:07:02 by smarty            #+#    #+#             */
/*   Updated: 2024/06/07 21:47:57 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handler(int signum)
{
	(void)signum;
//	rl_on_new_line();
	//todo new line
}

void quittt(int signum)
{
	(void) signum;

//	free_tab(data->env);
//	free(data->line);
	return ;
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	signal(SIGINT, handler);
	signal(SIGQUIT, quittt);
	if (ac != 1 ||av[0][0] != '.')
		return(printf("please enter valid argument\n"));
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("alloc fail\n"));
	minishell(data, env);
	free(data);
}