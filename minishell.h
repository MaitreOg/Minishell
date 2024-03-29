/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:53:58 by smarty            #+#    #+#             */
/*   Updated: 2024/03/29 17:28:55 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_data
{
	char **env;
	char *line;
	char ***tab;
}		t_data;

void    get_env(t_data *data, char **env);
void    minishell(t_data *data);
int		ft_strcmp(char *s1, char *s2);
void    pwd(t_data *data);
void    line_to_token(t_data *data);
char	*ft_strstr(char *str, char *to_find);
char	**ft_split(char *str, char c);

#endif