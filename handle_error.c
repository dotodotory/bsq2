/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiykim <jiykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:56:29 by jiykim            #+#    #+#             */
/*   Updated: 2020/11/03 16:20:28 by jiykim           ###   ########.fr       */
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
	c[0] = str[i - 3];
	c[1] = str[i - 2];
	c[2] = str[i - 1];
	if (c[0] == c[1] || c[1] == c[2] || c[2] == c[0])
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

int ft_read_file(int fd, char *buf)
{
	t_read f;
	char *temp;
	int col_size;
	int cnt;

	f.flag = 0;
	cnt = 0;
	col_size = 0;
	while((f.rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		f.buf_i = 0;
		while(f.flag == 0 && buf[f.buf_i] != '\n')
			f.buf_i++;
		if (f.flag++ == 0)
		{
			temp = (char*)malloc(sizeof(char) * (f.buf_i +1));
			if(!ft_first_line(ft_strncpy(temp, buf, f.buf_i)))
				return (0);
		}
		while(f.buf_i < f.rd)
		{
			if(buf[f.buf_i++] == '\n')
			{
				g_col = col_size;
				col_size = -1;
				cnt++;
			}
			col_size++;
		}
	}
	if(cnt != g_row+1)
		return (-1);
	return (1);
}

int	is_in_string(char buf_c)
{
	if (buf_c == c[0])
		return (1);
	if (buf_c == c[1])
		return (0);
	return (-1);
}

int 	ft_read_file2(int **map, int fd2, char buf2[])
{
	t_read f2;
	int m_i[2];

	f2.flag = 0;
	m_i[0] = 1;
	m_i[1] = 1;
	while (0 < (f2.rd = read(fd2, buf2, BUFF_SIZE)))
	{
		f2.buf_i = 0;
		while (f2.buf_i < f2.rd)
		{
			while (f2.flag == 0 && buf2[f2.buf_i] != '\n')
				f2.buf_i++;
			if (f2.flag++ == 0)
				f2.buf_i++;	
			if (buf2[f2.buf_i] == '\n')
			{
				if (m_i[1] - 1 != g_col)
					return (-1);
				map[m_i[0]][m_i[1]] = -1;
				m_i[0]++;
				m_i[1] = 1;
				
			}
			else if ((map[m_i[0]][m_i[1]++] = is_in_string(buf2[f2.buf_i])) == -1)
					return (-1);
			f2.buf_i++;		
		}
		
	}
	
	map[m_i[0]] = 0;
	return (1);
}
