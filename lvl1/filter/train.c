#define _GNU_SOURCE
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 50
#endif

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void filter(char *s, char *target)
{
	int i = 0;
	int j = 0;
	int tar = 0;
	int len = strlen(target);
	while(s[i])
	{
		if (s[i] == target[0])
		{
			j = i;
			tar = 0;
			while(s[j] == target[tar])
			{
				j++;
				tar++;
			}
			if (tar == len)
			{
				tar = 0;
				while(tar < len)
				{
					write(1, "*", 1);
					tar++;
				}
				i += len;
			}
			else
			{
				write(1, &s[i], 1);
				i++;
			}
		}
		else
		{
			write(1, &s[i], 1);
			i++;
		}
	}
}

int main(int argc, char **argv)
{
	if (argc != 2 || argv[1][0] == '\0')
		return 1;

	char temp[BUFFER_SIZE];
	char *buffer;
	char *result = NULL;
	int bytes = 0;
	int total_read = 0;
	while((bytes = read(0, temp, BUFFER_SIZE)) > 0)
	{
		buffer = realloc(result, total_read + bytes);
		if (!buffer)
		{
			perror("Error");
			return 1;
		}
		result = buffer;
		memmove(result + total_read, temp, bytes);
		total_read += bytes;
		result[total_read] = '\0';
	}
	if (bytes < 0)
	{
		perror("Error");
		free(result);
		return 1;
	}
	if (!result)
		return 1;
	filter(result, argv[1]);
	free(result);
	return 0;
}