#include <unistd.h>
#include <stdlib.h>

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void print_solution(int *pos)
{
	int i = 0;
	int first = 1;
	while(pos[i])
	{
		if (!first)
			printf(" ");
		printf("%d", pos[i]);
		i++;
	}
}

int is_safe(int *pos, int row, int col)
{
	int i = 0;
	while(i < col)
	{
		if (pos[i] == row)
			return 0;
		if(ft_abs(pos[i] - row) == col - i)
			return 0;
		i++;
	}
	return 1;
}

void solve(int *pos, int n, int col)
{
	if (col == n)
	{
		print_solution(pos);
		return;
	}
	while(row < n)
	{
		if(is_safe(pos, row, col))
		{
			pos[col] = row;
			solve(pos, n, col + 1);
		}
		row++;
	}
}