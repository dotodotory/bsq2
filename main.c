/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiykim <jiykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:29:08 by jiykim            #+#    #+#             */
/*   Updated: 2020/11/03 16:44:52 by jiykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

int	is_error(int nb)
{
	if (nb == 0)
		write(1, "Error\n", 6);
	else if (nb == -1)
	{
		write(1, "Map Error\n", 10);
		return (0);
	}
	return (nb);
}

void	ft_free_map(int **ptr)
{
	int ptr_i;

	ptr_i = 0; 
	printf("free start\n");
	while(ptr_i < g_row + 2)
	{
		printf("a\n");
		free(ptr[ptr_i++]);
		printf("b\n");
	}
	printf("1free\n");
	free(ptr); 
	printf("2free\n");
}

int	ft_open_file(char *file, char *buf)
{
	int open_f;
	int fd;

	if (0 < (fd = open(file, O_RDONLY)))
	{
		open_f = ft_read_file(fd, buf);
		close(fd);
	}
	else
		return (0);
	return (open_f);
}

int	ft_open_file2(char *file2, char *buf2)
{
	int open_f2;
	int i;
	int **map;
	int fd2;

	i = 0;
	map = (int **)malloc(sizeof(int *) * g_row + 2);
	printf("mallocas\n");
	while (i < g_row + 2)
	{
		map[i] = ft_calloc(map[i], g_col + 1);
		i++;
	}
	if (0 < (fd2 = open(file2, O_RDONLY)))
	{
		open_f2 = ft_read_file2(map, fd2, buf2);
		if (open_f2 == -1)
		{
			ft_free_map(map);
			return(-1);
		}
	}
	else
		return (0);
	chk(map);
	print_map(map, c);
	ft_free_map(map);
	return (1);
}

int		main(int argc, char **argv)
{
	int main_f;
	char buff[BUFF_SIZE];

	if (argc == 2)
	{
		main_f = ft_open_file(argv[1], buff);
		if (!is_error(main_f))
			return (0);
		main_f = ft_open_file2(argv[1], buff);
		if (!is_error(main_f))
			return (0);
	}
	else
		is_error(0);
	return (0);
}
