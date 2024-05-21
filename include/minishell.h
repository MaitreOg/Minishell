/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:53:58 by smarty            #+#    #+#             */
/*   Updated: 2024/04/04 20:40:59 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

//type 1 = commande   type 2 = redirection  type 3 = pipe  type 4 = file
typedef struct s_token
{
	char *order;
	int	type;

}		t_token;

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
char	**ft_split2(char *str, char*operator);
int 	is_verif(char *str, int i);
char	*find_var(char **env, char *var);
int		ft_strlen(char *str);
char 	*replace_var(t_data *data, char *str);
char	*ft_strjoin(char *s1, char *s2);
int 	is_verif_quotes(char *str, int i);
char	*ft_strdup(char *s);
char	*delete_quotes(char *str);
#endif