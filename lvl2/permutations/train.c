#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_isalpha(char c)
{
	return((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int ft_strlen(char *s)
{
	int i = 0;
	while(s[i])
		i++;
	return i;
}

char* order_string(char *s)
{
	int i = 0;
	int len = ft_strlen(s);
	while (i < len - 1)
	{
		if (s[i] > s[i + 1])
		{
			char temp = s[i];
			s[i] = s[i + 1];
			s[i + 1] = temp;
			i = 0;
		}
		i++;
	}
	return s;
}

void generate_perm(char *source, char *result, int pos, int mask)
{
	int i = 0;
	int source_len = ft_strlen(source);
	if (pos == source_len)
	{
		write(1, result, source_len);
		write(1, "\n", 1);
		return;
	}
	while (i < source_len)
	{
		if (!(mask & (1 << i)))
		{
			result[pos] = source[i];
			generate_perm(source, result, pos + 1, mask | (1 << i));
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	if(argc != 2 || argv[1][0] == '\0' || !argv[1])
		return 0;
	char *result;
	for (int i = 0; argv[1][i]; i++ )
		if(!ft_isalpha(argv[1][i]))
			return 1;
	int len = ft_strlen(argv[1]);
	char *source = order_string(argv[1]);
	result = calloc(len + 1, 1);
	generate_perm(source, result, 0, 0);
	free(result);
	return 0;
}
