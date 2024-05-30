/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 00:21:40 by smarty            #+#    #+#             */
/*   Updated: 2023/10/26 00:43:15 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif /*buffer size*/

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*read_function(int fd, char *stash);
char	*find_str(char *stash);
char	*next_line(char *stash);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_strlen_newl(char *stash);
int		check_newl(char *stash, int value_read);

#endif /*get_next_line*/   
