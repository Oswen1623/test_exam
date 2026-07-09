#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

void	ft_swap(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

char	*order_string(char *s)
{
	int	len;
	int	swapped;
	int	i;

	len = ft_strlen(s);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < len - 1)
		{
			if (s[i] > s[i + 1])
			{
				ft_swap(&s[i], &s[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
	return (s);
}

/*
** Génère les permutations en utilisant un bitmask pour suivre les indices utilisés.
** 'mask' garde une trace des positions (indices) de la chaîne 'source' déjà placées.
*/
void	generate_permutations(char *source, char *result, int pos, int mask)
{
	int	source_len;
	int	i;

	source_len = ft_strlen(source);
	if (pos == source_len)
	{
		write(1, result, source_len);
		write(1, "\n", 1);
		return ;
	}
	i = 0;
	while (i < source_len)
	{
		// Vérifie si le i-ème caractère a déjà été utilisé (si le i-ème bit est à 0)
		if (!(mask & (1 << i)))
		{
			result[pos] = source[i];
			// On relance la récursion en activant le i-ème bit (mask | (1 << i))
			generate_permutations(source, result, pos + 1, mask | (1 << i));
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	int		len;
	char	*result;
	char	*source;

	if (argc != 2)
		return (1);
	if (ft_strlen(argv[1]) == 0 || (argv[1][0] == ' ' && !argv[1][1]))
		return (0);
	i = 0;
	while (argv[1][i])
	{
		if (!ft_isalpha(argv[1][i]))
			return (0);
		i++;
	}
	len = ft_strlen(argv[1]);
	result = calloc(len + 1, 1);
	if (!result)
		return (1);
	source = order_string(argv[1]);
	// On initialise le masque à 0 (aucun caractère utilisé au départ)
	generate_permutations(source, result, 0, 0);
	free(result);
	return (0);
}
