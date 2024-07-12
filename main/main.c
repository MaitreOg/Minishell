/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:07:02 by smarty            #+#    #+#             */
/*   Updated: 2024/07/12 13:32:36 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_bzero(void *s, size_t n)
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

void	ctrlback(void)
{
	struct sigaction	ouais;

	ft_bzero(&ouais, sizeof(ouais));
	ouais.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &ouais, NULL);
}

void	ctrlc(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("\0", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*str;
	char	*tmp;

	signal(SIGINT, ctrlc);
	ctrlback();
	if (ac != 1 || av[0][0] == '!')
		return (printf("please enter valid argument\n"));
	data = malloc(sizeof(t_data));
	if (!data)
	{
		return (printf("alloc fail\n"));
	}
	get_env(data, env);
	tmp = ft_strjoin("SHELL=", "/bin/minishell", 0, 0);
	str = "SHELL=/bin/minishell";
	if (ft_strcmp(data->env[get_env_index(data, "SHELL=")], str) != 1)
		export_env(data, tmp);
	else
		shell_lvl_incr(data);
	free(tmp);
	minishell(data);
	free(data);
}
