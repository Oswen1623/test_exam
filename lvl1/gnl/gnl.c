#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;

	if (n == 0 || dest == src)
		return (dest);
	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t res;

	res = 0;
	if (!s)
		return (0);
	while (s[res])
		res++;
	return (res);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1;
	char *tmp;

	if (!s2 && size2 != 0)
		return (0);
	size1 = 0;
	if (*s1)
		size1 = ft_strlen(*s1);
	tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	if (size1 > 0)
		ft_memcpy(tmp, *s1, size1);
	if (size2 > 0)
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
	size_t i;
	unsigned char *d;
	const unsigned char *s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == s || n == 0)
		return (dest);
	if (d > s)
	{
		i = n;
		while (i > 0)
		{
			i--;
			d[i] = s[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
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
	line = get_next_line(fd);
	while (line)
	{
		printf("Line %d : %s", i, line);
		line = get_next_line(fd);
		i++;
	}
}
