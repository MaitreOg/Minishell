/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:53:58 by smarty            #+#    #+#             */
/*   Updated: 2024/05/29 16:58:39 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <signal.h>
# include <stdarg.h>
#include <fcntl.h>

enum Type
{
	TYPE_ORDER,     //0
	TYPE_ROUT,      //1
	TYPE_RIN,       //2
	TYPE_ROUT_APP,  //3
	TYPE_LIMITER, //4
	TYPE_PIPE,      //5
	TYPE_FILE       //6
};

typedef struct s_list
{
	char *content;
	enum Type content_type;
	struct s_list	*next;
}		t_list;

typedef struct s_data
{
	char **env;
	char *line;
	t_list *line_lst;
}		t_data;

void    get_env(t_data *data, char **env);
void    minishell(t_data *data);
int		ft_strcmp(char *s1, char *s2);
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
void	token_to_lst(char **tab, t_data *data);
t_list	*lst_add(t_list *lst, char *data);
int		*ft_lstprint(t_list *lst);
t_list	*lst_prev(t_list *lst, t_list *original);
char	**find_path(char **env);
void	free_cmd(char **cmd);
void	free_path(char **path);
void execute(t_data *data, t_list *lst);

//execution
void compute(t_data *data);

//redirection && pipe
void    redirect_output(t_data *data, t_list *lst, int append);
void    redirect_input(t_data *data, t_list *lst);
void    limiter(t_data *data, t_list *lst);
void	pipes(t_list *cmd1, t_list *cmd2, t_data *data);

//builtins
void	ft_pwd();
void	echo(char *str, int arg);
void	ft_cd(char *str);
void	env(t_data *data);
void	unset(t_data *data, ...);

#endif