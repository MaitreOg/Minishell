/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliradet <oliradet@42student.perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:50:43 by oliradet          #+#    #+#             */
/*   Updated: 2024/07/09 05:48:21 by oliradet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_env(t_data *data, char *name)
{
	int	i;
	int	y;

	i = 0;
	while (data->env[i])
	{
		y = 0;
		while (data->env[i][y] && data->env[i][y] != '=')
			y++;
		if (ft_strncmp(data->env[i], name, y) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	edit_env(t_data *data, char *name, char *value)
{
	int	i;
	int	y;
	char  *new_value;

	i = 0;
	while (data->env[i])
	{
		y = 0;
		while (data->env[i][y] && data->env[i][y] != '=')
			y++;
		if (ft_strncmp(data->env[i], name, y) == 0)
		{
			free(data->env[i]);
			new_value = malloc(ft_strlen(name) + ft_strlen(value) + 2); // +2 for '=' and '\0'
			strcpy(new_value, name);
			data->env[i] = new_value;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	valid_env_name(char *name)
{
	int	i;

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

int	valid_env_name_export(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (0);
	i++;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*value_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (str + i);
	return (NULL);
}

char	**ft_realloc_tab(char **tab, char *str)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup_v2(tab[i]);
		free(tab[i]);
		i++;
	}
	new_tab[i] = ft_strdup_v2(str);
	new_tab[i + 1] = NULL;
	free(tab);
	tab = NULL;
	return (new_tab);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

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

int	get_env_index(t_data *data, char *name)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, ft_strlen(name)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_ispresent(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	nb;

	i = 0;
	neg = 1;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
        || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb * neg);
}

void shell_lvl_decr(t_data *data)
{
		int value;

		value = ft_atoi(value_env(data->env[get_env_index(data, "SHLVL=")]) + 1);
		if (value > 1) {
			printf("value = %d\n", value);
			value--;
			printf("value = %d\n", value);
//			export_env(data, ft_strjoin("SHLVL=", ft_itoa(value), 0, 0));
			printf("UPDATE");
			printf("env : %s\n", ft_strjoin("SHLVL=", ft_itoa(value), 0, 0));
			edit_env(data, "SHLVL=", ft_itoa(value));
		}

}

void shell_lvl_incr(t_data *data)
{
	int value;
	value = ft_atoi(value_env(data->env[get_env_index(data, "SHLVL=")]) + 1);
	value++;
	export_env(data, ft_strjoin("SHLVL=", ft_itoa(value),0,0));
}

int env_has_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}