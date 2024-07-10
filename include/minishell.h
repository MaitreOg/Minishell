/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:53:58 by smarty            #+#    #+#             */
/*   Updated: 2024/06/08 22:09:31 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../utils/get_next_line/get_next_line.h"

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
	pid_t	*childpid;
	int return_value;
	int in_progress;
	int execute;
	char **env;
	int *keys_env;
	char *line;
	int stdin;
	t_list *line_lst;
	int 	ret;
}		t_data;

void    minishell(t_data *data);


//free && error
void	free_cmd(char **cmd);
void	free_exec(char **path, char **cmd, t_data *data);
void	free_path(char **path);
void	free_all(t_data *data);
void	perror_process(t_data *data, char *error);
void	free_tab(char **tab);
void	redirect_error(t_data *data, char *error, t_list *lst);
void	order_not_found(t_data *data, char *order);
void 	free_compute(t_data *data);


//lst utils
t_list	*lst_prev(t_list *lst, t_list *original);
t_list	*lst_add(t_list *lst, char *data);
t_list	*next_order(t_list *lst);
int		*ft_lstprint(t_list *lst);
int		last_order(t_list *lst);


//parsing
char	*find_var(char **env, char *var);
char	*find_var2(char **env, char *var);
int		is_verif_double(char *str, int i);
int 	is_verif_quotes(char *str, int i);
char 	*replace_var(t_data *data, char *str, int i, int y);
char	*delete_quotes(char *str);
void	token_to_lst(char **tab, t_data *data);
void    line_to_token(t_data *data);
char	**find_path(char **env);


//utils
void	is_not_found(t_data *data, char **cmd, char **path, int i);
char	*build_arg_path(char **cmd, char **path, int i);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
void	delete_space(t_list *lst);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strjoin(char *s1, char *s2, int z, int y);
char	*ft_strdup(char *s);
char	**ft_split(char *str, char c);
char	** ft_split2(char *str, char*operator);
int		count_word_arg(char *s, char c);
int		count_word2(char *str, char *operator);
char	**cut_split_2(char *str, char **split, char *operator);
char	**cpyword_arg(char **str, char *s, char c, int i);
char	**ft_split_arg(char *str, char c);
void    get_env(t_data *data, char **env);
int 	is_verif(char *str, int i);
int		ft_strmcmp(char *s1, char *s2, int y);
void	alloc_pid(t_data *data);
int 	nb_order(t_data *data);
char	*ft_strdup_v2(char *s);
char	*ft_itoa(int n);
int		is_only_space(char *str);

//execution
void	compute(t_data *data);
void	fork_order(t_data *data, t_list *lst);
void 	execute(t_data *data, t_list *lst);


//redirection && pipe
void 	compute_operator(t_data *data, t_list *lst);
void    redirect_output(t_data *data, t_list *lst, int append);
void    redirect_input(t_data *data, t_list *lst);
void    limiter(t_data *data, t_list *lst);
void	pipes(t_data *data, t_list *order, int i);


//builtins
int		ft_pwd(void);
int		echo(char *str, int arg);
int		ft_cd(t_data *data, char *str);
int		ft_env(t_data *data);
int		ft_unset(t_data *data, char *args);
int 	find_env(t_data *data, char *name);
int 	edit_env(t_data *data, char *name, char *value);
int 	ft_isalpha(int c);
int 	ft_isalnum(int c);
int 	valid_env_name(char *name);
int 	valid_env_name_export(char *name);
char 	*value_env(char *str);
char 	**ft_realloc_tab(char **tab, char *str);
int 	ft_ispresent(char *str, char c);
int 	get_env_index(t_data *data, char *name);
int 	ft_strncmp(const char *s1, const char *s2, size_t n);
int 	export_env(t_data *data, char *str);
int		ft_exit(t_data *data);
int 	ft_atoi(const char *str);
void	shell_lvl_decr(t_data *data);
void	shell_lvl_incr(t_data *data);
int		env_has_value(char *str);
void	print_sorted_env(t_data *data);
int		ft_size_tab(char **tab);

#endif