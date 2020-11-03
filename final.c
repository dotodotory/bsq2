#include "header.h"

int ret[3];

int *ft_calloc(int *addr, int size)
{
	int i;
	
	addr = (int*)malloc(sizeof(int) * (size+1));
	i = 0;
	while (i < size)
		addr[i++] = 0;
	addr[i] =-1;
	return addr;
}

int minimum(int i, int j, int **map)
{
	int min;

	min = (map[i-1][j] > map[i][j-1] ? map[i][j-1] : map[i-1][j]);
	min = (min > map[i-1][j-1] ? map[i-1][j-1] : min);
	return min;
}

void chk(int **map)
{	
	int i;
	int j;

	i = 1;
	while(map[i] != 0)
	{
		j = 1;
		while(map[i][j] !=-1)
		{
			if(map[i][j] != 0)
			{
				map[i][j] = minimum(i, j, map)+1;
				if(map[i][j] > ret[0])
				{
					ret[0] =map[i][j];
					ret[1]=i;
					ret[2]=j;
				}
			}
			j++;
		}
		i++;
	}
}

void print_map(int **map, char *moji)
{
	int i;
	int j;

	i = 1;
	j = 1;
	while(map[i] !=0)
	{
		j = 1;
		while(map[i][j] != -1 )
		{
			if(i >= ret[1] - ret[0] +1 && i <=ret[1] &&
			   j >= ret[2] - ret[0] +1 && j <=ret[2])
				write(1, &moji[2], 1);
			else if(map[i][j] == 0)
				write(1, &moji[1], 1);
			else
				write(1, &moji[0], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
