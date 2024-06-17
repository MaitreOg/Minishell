#include "../include/minishell.h"

int	len_number(int n)
{
	int		i;
	long	y;

	i = 1;
	y = n;
	if (n < 0)
	{
		i++;
		y *= -1;
	}
	while (y > 9)
	{
		y = y / 10;
		i++;
	}
	return (i);
}

char	*tab(char *s, long j, int z, int n)
{
	long	y;

	y = 1;
	if (n < 0)
		z--;
	while (--z)
		y *= 10;
	if (n < 0)
		s[z++] = '-';
	while (y)
	{
		s[z++] = ((j / y) + '0');
		j = j - ((j / y) * y);
		y /= 10;
	}
	if (j == 0 && len_number(n) > z)
	{
		while (len_number(n) > z)
			s[z++] = '0';
	}
	s[z] = 0;
	return (s);
}

char	*ft_itoa(int n)
{
	int		z;
	long	j;
	char	*s;

	j = n;
	if (j < 0)
		j *= -1;
	z = len_number(n);
	s = malloc(sizeof(char) * (z + 1));
	if (!s)
		return (NULL);
	s = tab(s, j, z, n);
	return (s);
}
