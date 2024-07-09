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

void	ctrlc(int signum)
{
	(void)signum;

	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void ctrlback(void)
{
	struct sigaction	ouais;

	ft_bzero(&ouais, sizeof(ouais));
	ouais.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &ouais, NULL);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	signal(SIGINT, ctrlc);
	//sigaction sigquit vers sigin
	ctrlback();
	if (ac != 1 ||av[0][0] == '!')
		return(printf("please enter valid argument\n"));
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("alloc fail\n"));
	get_env(data, env);
	int value;

	value = ft_atoi(value_env(data->env[get_env_index(data, "SHLVL=")]) + 1);
	if (value == 1)
		export_env(data, ft_strjoin("SHLVL=", "1", 0, 0));
	else
		shell_lvl_incr(data);
	minishell(data, env);
	free(data);
}