/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:24:25 by oliradet          #+#    #+#             */
/*   Updated: 2024/05/25 02:24:25 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int ft_isalnum(int c)
{
	if (ft_isalpha(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int valid_env_name(char *name)
{
	int i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (0);
	i++;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *str1;
	unsigned char *str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n--)
	{
		if (*str1 != *str2 || *str1 == '\0' || *str2 == '\0')
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}

int get_env_index(t_data *data, char *name)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, ft_strlen(name)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int ft_ispresent(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * unset all variable specified
 * @param data
 * @param args the table of variable to unset
 */
void ft_unset(t_data *data, char **args)
{

	int i;
	int index;

	i= 0;
	while (args[i])
	{
		if (!valid_env_name(args[i]) || ft_ispresent(args[i], '='))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
			data->ret = 1;
		}
		else
		{
			index = get_env_index(data, args[i]);
			if (index != -1)
			{
				free(data->env[index]);
				while (data->env[index])
				{
					data->env[index] = data->env[index + 1];
					index++;
				}
			}
		}
	}
}