/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:51:35 by oliradet          #+#    #+#             */
/*   Updated: 2024/07/09 20:51:35 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_split2(char *str, char*operator)
{
	int		nb;
	char	**split;

	nb = count_word2(str, operator);
	split = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!split)
		return (NULL);
	return (cut_split_2(str, split, operator));
}

char	**ft_split_arg(char *str, char c)
{
	int		nb;
	char	**ss;

	nb = count_word_arg(str, c);
	ss = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!ss)
		return (NULL);
	return (cpyword_arg(ss, str, c, 0));
}
