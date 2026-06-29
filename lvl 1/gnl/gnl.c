#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!src && !dest)
		return (NULL);
	while (n > 0 && ((char *)src)[n])
	{
		((char *)dest)[n] = ((char *)src)[n];
		n--;
	}
	((char *)dest)[++n] = '\0';
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	res;

	res = 0;
	if (!s || !s[res])
		return (0);
	while (s[res])
	{
		s++;
		res++;
	}
	return (res);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	size1 = ft_strlen(*s1);
	tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	limit;
	size_t	i;

	if (dest > src)
		return (ft_memmove(dest, src, n));
	else if (dest == src)
		return (dest);
	limit = ft_strlen((char *)src) - 1;
	i = 0;
	while (i <= limit)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char		*ret;
	char		*temp;
	int			read_ret;

	ret = NULL;
	while (1)
	{
		temp = ft_strchr(b, '\n');
		if (temp)
		{
			if (!str_append_mem(&ret, b, temp - b + 1))
				return (free(ret), NULL);
			ft_memmove(b, temp + 1, ft_strlen(temp + 1) + 1);
			return (ret);
		}
		if (!str_append_str(&ret, b))
			return (NULL);
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret <= 0)
		{
			b[0] = '\0';
			if (ret && *ret)
				return (ret);
			free(ret);
			return (NULL);
		}
		b[read_ret] = '\0';
	}
}

int	main(void)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open("test", O_RDONLY);
	if (fd < 0)
	{
		printf("Can't open file.\n");
		return (1);
	}
	while (get_next_line(fd) != NULL)
	{
		line = get_next_line(fd);
		printf("Line %d : %s\n", i, line);
		i++;
	}
}
