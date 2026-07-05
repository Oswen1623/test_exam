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

int	ft_strchr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
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

void	generate_permutations(char *source, char *result, int pos)
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
		if (!ft_strchr(result, source[i]))
		{
			result[pos] = source[i];
			generate_permutations(source, result, pos + 1);
			result[pos] = '\0';
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
	generate_permutations(source, result, 0);
	free(result);
	return (0);
}

/*
 * VERSIÓN ALTERNATIVA CON ALGORITMO DE HEAP:
 * (Más eficiente para strings largos)
 */
void	heap_permute(char *str, int size)
{
	int	i;

	// Caso base
	if (size == 1)
	{
		puts(str);
		return ;
	}
	for (i = 0; i < size; i++)
	{
		heap_permute(str, size - 1);
		// Si size es impar, intercambiar primer y último
		// Si size es par, intercambiar i-ésimo y último
		if (size % 2 == 1)
			ft_swap(&str[0], &str[size - 1]);
		else
			ft_swap(&str[i], &str[size - 1]);
	}
}
