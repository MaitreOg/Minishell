/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main .c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:04:05 by smarty            #+#    #+#             */
/*   Updated: 2023/10/23 14:25:16 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main ()
{
	int	fd;

	fd = open("./fichier.txt", O_RDONLY);
	// get_next_line(fd);
	// get_next_line(fd);
	// get_next_line(fd);
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	close(fd);
}