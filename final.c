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

/*int main(int argc, char **argv)
{
	int fd;
	int line;
	int rd;
	int i;
	char buf[1024];
//	char empty;
//	char dis;
//	char ful;
	int **arr;
	int j;
	int len;
	int k;
	char sign[4];
//	int *maxpos;

	fd = open(argv[1], O_RDONLY);
	rd = read(fd, buf, sizeof(buf));
	line = buf[0]  - '0';
	sign[0] = buf[1];
	sign[1] = buf[2];
	sign[2] = buf[3];
	sign[3] = '\n';
	i = 5;
	j = 0;
	k = 0;
	arr = (int**)malloc(sizeof(int*) * (line+1));
	while(buf[i] != '\n')
		i++;
	len = i - 5;
	i = 0;
	while (i< line)
		arr[i++] = (int*)malloc(sizeof(int)*(len+1));
	i = 5;
	while(i< rd)
	{
		if(buf[i] == '\n')
		{
			arr[j][k] = -1;
			j++;
			k = 0;
		}
		else if (buf[i] == sign[0])
			arr[j][k++] = 1;
		else
			arr[j][k++] = 0;
		i++;
	}
	while((rd = read(fd, buf, sizeof(buf))) > 0)
	{
		i = 0;
		while(i< rd)
		{
			if(buf[i] == '\n')
			{
				arr[j][k] = -1;
				j++;
				k = 0;
			}
			else if (buf[i] == sign[0])
				arr[j][k++] = 1;
			else
				arr[j][k++] = 0;
			i++;
		}
	}
	arr[j] = 0;
	printf("initial map\n");
	for (i =0 ;i< line; i++)
	{
		for(j = 0 ; j< len; j++)
			printf("%d", arr[i][j]);
		printf("\n");
	}
	printf("\n");
	chk(arr);
	printf("max and pos %d%d%d\n", ret[0], ret[1], ret[2]);
//	printf("sign : %s\n", sign);
	printf("after transform\n");
	for (i =0 ;i< line; i++)
	{
		for(j = 0 ; j< len; j++)
			printf("%d", arr[i][j]);
		printf("\n");
	}
	printf("answer\n");
	print_map(arr, sign);
	return 0;
}
*/



