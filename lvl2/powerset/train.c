#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	*set;
	int	i;
	int	size;
	int	target;
	int	total_combinations;
	int	mask;
	int	curr_sum;
	int found = 0;
	int first = 0;

	if (argc < 3)
		return (0);
	size = argc - 2;
	set = malloc(sizeof(int) * size);
	if (!set)
		return 1;
	mask = 0;
	i = 0;
	curr_sum = 0;
	target = atoi(argv[1]);
	while (i < size)
	{
		set[i] = atoi(argv[i + 2]);
		i++;
	}
	total_combinations = 1 << size;
	while (mask < total_combinations)
	{
		curr_sum = 0;
		for(i = 0; i < size ; i++)
			if ((mask >> i) & 1)
				curr_sum += set[i];
		if (curr_sum == target)
		{
			i = 0;
			found = 1;
			first = 1;
			for(i = 0; i < size ; i++)
			{
				if ((mask >> i) & 1)
				{
					if(first == 0) //si ce n'est pas le premier, mettre un espace avant
						printf(" %d", set[i]);
					else
						printf("%d", set[i]);
					first = 0;
				}
			}
			printf("\n");
		}
		mask++;
	}
	if (!found)
		printf("\n");
	return 0;
}
