#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	*set;
	int	size;
	int	target;
	int	total_combinations;
	int	found;
	int	current_sum;
	int	first;

	if (argc < 3)
	{
		printf("\n");
		return (0);
	}
	target = atoi(argv[1]);
	size = argc - 2;
	set = malloc(size * sizeof(int));
	if (!set)
		return (1);
	for (int i = 0; i < size; i++)
	{
		set[i] = atoi(argv[i + 2]);
	}
	// total_combinations = 2^size (en utilisant le décalage de bits : 1 << size)
	total_combinations = 1 << size;
	found = 0;
	// On teste toutes les combinaisons de 0 à (2^size - 1)
	for (int mask = 0; mask < total_combinations; mask++)
	{
		current_sum = 0;
		// Étape 1 : Calculer la somme de la combinaison actuelle
		for (int i = 0; i < size; i++)
		{
			if ((mask >> i) & 1)
			{ // Si le i-ème bit du masque est à 1
				current_sum += set[i];
			}
		}
		// Étape 2 : Si la somme correspond,
			// on ré-analyse le masque pour afficher
		if (current_sum == target)
		{
			first = 1;
			for (int i = 0; i < size; i++)
			{
				if ((mask >> i) & 1)
				{
					if (!first)
					{
						printf(" ");
					}
					printf("%d", set[i]);
					first = 0;
				}
			}
			printf("\n");
			found = 1;
		}
	}
	if (!found)
	{
		printf("\n");
	}
	free(set);
	return (0);
}
