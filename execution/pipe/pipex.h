/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:37:15 by smarty            #+#    #+#             */
/*   Updated: 2023/12/16 03:09:22 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"

char	*ft_strstr(char *str, char *to_find);
char	**ft_split(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putendl_fd(char *s, int fd);
int		ft_strlen(char *str);
void	free_cmd(char **cmd);
void	free_path(char **path);
char	**find_path(char **env);
void	pipe_process(char **av, char **env, int i);
void	ex_cmd(char **av, char **env, int y);
void	create_childpid(char **av, char **env, int y);
int		main(int ac, char **av, char **env);
int		here_doc(char **av);
int		ft_strncmp(char *s1, char *s2, int len);
int		ft_strlen(char *str);
#endif