/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiykim <jiykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:56:29 by jiykim            #+#    #+#             */
/*   Updated: 2020/11/03 19:43:19 by jiykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

int	ft_atoi(char *str, int size)
{
	int a_i;

	a_i = 0;
	while (str[a_i] == ' ' || (str[a_i] >= 9  && str[a_i] <= 13))
		a_i++;
	while (a_i < size)
	{
		if (!(str[a_i] >= '0' && str[a_i] <= '9'))
			return (0);
		g_row = g_row * 10 + (str[a_i] - '0');
		a_i++;
	}
	return (1);
}

int	ft_first_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (!(ft_atoi(str, i - 3)))
	{
		free(str);
		return (0);
	}
	g_c[0] = str[i - 3];
	g_c[1] = str[i - 2];
	g_c[2] = str[i - 1];
	if (g_c[0] == g_c[1] || g_c[1] == g_c[2] || g_c[2] == g_c[0])
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

int ft_read_file(int fd, char *buf)
{
	char *temp;

	while((g_f.rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		g_f.buf_i = 0;
		while(g_f.flag == 0 && buf[g_f.buf_i] != '\n')
			g_f.buf_i++;
		if (g_f.flag++ == 0)
		{
			temp = (char*)malloc(sizeof(char) * (g_f.buf_i +1));
			if(!ft_first_line(ft_strncpy(temp, buf, g_f.buf_i)))
				return (0);
		}
		while(g_f.buf_i < g_f.rd)
		{
			if(buf[g_f.buf_i++] == '\n')
			{
				g_col = g_col_size;
				g_col_size = -1;
				g_cnt++;
			}
			g_col_size++;
		}
	}
	return (g_cnt != g_row + 1 ? -1 : 1);
}

int	is_in_string(char buf_c)
{
	if (buf_c == g_c[0])
		return (1);
	if (buf_c == g_c[1])
		return (0);
	return (-1);
}

int 	ft_read_file2(int **map, int fd2, char buf2[])
{
	g_m_i[0] = 1;
	g_m_i[1] = 1;
	while (0 < (g_f2.rd = read(fd2, buf2, BUFF_SIZE)))
	{
		g_f2.buf_i = -1;
		while (++g_f2.buf_i < g_f2.rd)
		{
			while (g_f2.flag == 0 && buf2[g_f2.buf_i] != '\n')
				g_f2.buf_i++;
			if (g_f2.flag++ == 0) 
				g_f2.buf_i++;
			if (buf2[g_f2.buf_i] == '\n')
			{
				if (g_m_i[1] - 1 != g_col)
					return (-1);
				map[g_m_i[0]++][g_m_i[1]] = -1;
				g_m_i[1] = 1;
				
			}
			else if ((map[g_m_i[0]][g_m_i[1]++] = is_in_string(buf2[g_f2.buf_i])) == -1)
				return (-1);
		}
		
	}
	return (1);
}
