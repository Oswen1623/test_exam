#define _GNU_SOURCE
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	filter(char *buffer, const char *target)
{
	int				i;
	unsigned int	target_len;
	i = 0;
	target_len = strlen(target);
	unsigned int target_i = 0;
	int j = 0;
	unsigned int target_j = 0;
	while (buffer[i])
	{
		target_i = 0;
		if (buffer[i] == target[0]) //si target[0] == buffer[i] -> on rentre dans la condition
		{
			j = i; //j reprend la ou i s'est arrete
			while (target[target_i] == buffer[j] && target[target_i] && buffer[j]) //tant que les char sont identiques
			{
				j++;
				target_i++;
			}
			if (target_i == target_len) //si on a atteint la fin de la target, on a trouve l'occurrence -> on remplace
			{
				target_j = 0;
				while (target_j < target_len)
				{
					write(1, "*", 1);
					target_j++;
				}
				i += target_len; //on fait reprendre i a la fin de l'occurrence
			}
			else if (target_i < target_len)//si on atteint pas la fin, occurrence incomplete donc on ecrit
			{
					write(1, &buffer[i], 1);
					i++;
			}
		}
		else //sinon on ecrit normalement la string
		{
			write(1, &buffer[i], 1);
			i++;
		}
	}
	// boucle sur l'affichage de la string
	// longueur de la string a changer
	// 3 index pour garder les emplacements des limites
	return (0);
}

int	main(int argc, char **argv)
{
	int				bytes;
	char			temp[BUFFER_SIZE];
	char			*res;
	char			*	buffer;
	unsigned long	total_read;

	bytes = 0;
	res = NULL;
	buffer = NULL;
	if (argc != 2 || !argv[1] || argv[1][0] == '\0')
		return (1);
	while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
	{
		buffer = realloc(res, total_read + bytes + 1);
		// agrandir la taille du buffer pour accueillir la nouvelle lecture
		if (!buffer) // erreur de realloc
		{
			free(res);
			perror("realloc");
			return (1);
		}
		res = buffer;
		memmove(res + total_read, temp, bytes);
		// on copie le contenu de temp dans res a partir de l'index total_read
		total_read += bytes;
		// on additionne dans le nombre total de bytes lus
		res[total_read] = '\0';
	}
	if (bytes < 0) // erreur de read
	{
		free(res);
		perror("read");
		return (1);
	}
	if (!res)
		return (0);
	filter(res, argv[1]);
	// char *a = "ababcabababc";
	// char *b = "ababc";
	// filter(a, b);
	// printf("\n");
	return 0;
}
