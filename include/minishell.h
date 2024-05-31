/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:53:58 by smarty            #+#    #+#             */
/*   Updated: 2024/06/01 01:10:21 by smarty           ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/wait.h>
#include "../utils/get_next_line/get_next_line.h"

int g_exit_status;
int	g_sigint;


enum Type
{
	TYPE_ORDER,     //0
	TYPE_ROUT,      //1
	TYPE_RIN,       //2
	TYPE_ROUT_APP,  //3
	TYPE_LIMITER,   //4
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
	int o;
	int fdo;
	int in_progress;
	int execute;
	char **env;
	char *line;
	t_list *line_lst;
}		t_data;



void    minishell(t_data *data, char **env);


//free && error
void	free_cmd(char **cmd);
void	free_path(char **path);
void	free_all(t_data *data);
void	perror_process(t_data *data, char *error);
void	free_tab(char **tab);



//lst utils
t_list	*lst_prev(t_list *lst, t_list *original);
t_list	*lst_add(t_list *lst, char *data);
t_list	*next_order(t_list *lst);
int		*ft_lstprint(t_list *lst);


//parsing
char	*find_var(char **env, char *var);
int 	is_verif_quotes(char *str, int i);
char 	*replace_var(t_data *data, char *str);
char	*delete_quotes(char *str);
void	token_to_lst(char **tab, t_data *data);
void    line_to_token(t_data *data);
char	**find_path(char **env);


//utils
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
void	delete_space(t_list *lst);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strjoin(char *s1, char *s2, int z, int y);
char	*ft_strdup(char *s);
char	**ft_split(char *str, char c);
char	**ft_split2(char *str, char*operator);
void    get_env(t_data *data, char **env);
int 	is_verif(char *str, int i);


//execution
void	compute(t_data *data);
void	fork_order(t_data *data, t_list *lst);
void 	execute(t_data *data, t_list *lst);


//redirection && pipe
void 	compute_operator(t_data *data, t_list *lst);
void    redirect_output(t_data *data, t_list *lst, int append);
void    redirect_input(t_data *data, t_list *lst);
void    limiter(t_data *data, t_list *lst);
void	pipes(t_data *data, t_list *order);


//builtins
void	ft_pwd();
void	echo(char *str, int arg);
void	ft_cd(char *str);
void	env(t_data *data);
void	unset(t_data *data, ...);

#endif