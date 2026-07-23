#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	// if((char)c == '\0')
	// 	return NULL;
	while (s[i])
	{
		if(s[i] == c)
			return s + i;
		i++;
	}
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || dest == src)
		return (dest);
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	res;

	res = 0;
	if (!s)
		return (0);
	while (s[res])
		res++;
	return (res);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	size1 = 0;
	if (size2 == 0)
		return (1);
	if (*s1)
		size1 = ft_strlen(*s1);
	tmp = malloc((size2 + size1 + 1) * sizeof(char));
	if (!tmp)
	{
		free(*s1);
		*s1 = NULL;
		return (0);
	}
	if (*s1)
		ft_memcpy(tmp, *s1, size1);
	if(*s2)
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
	if (!dest && !src)
		return (NULL);
	if (dest == src || n == 0)
		return (dest);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	while (n > 0)
	{
		((char *)dest)[n - 1] = ((char *)src)[n - 1];
		n--;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*temp;
	int			bytes;
	char		*ret;

	temp = NULL;
	bytes = 0;
	ret = NULL;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	while (1)
	{
		temp = ft_strchr(buffer, '\n');
		if (!temp)
		{
			if (!str_append_str(&ret, buffer))
			{
				buffer[0] = '\0';
				return (NULL);
			}
			bytes = read(fd, buffer, BUFFER_SIZE);
			if (bytes < 0)
			{
				buffer[0] = '\0';
				return (free(ret), NULL);
			}
			if (bytes == 0)
			{
				buffer[0] = '\0';
				if (ret && *ret)
					return (ret);
				return (free(ret), NULL);
			}
			buffer[bytes] = '\0';
		}
		else
		{
			if (!str_append_mem(&ret, buffer, temp - buffer + 1))
			{
				buffer[0] = '\0';
				return (NULL);
			}
			ft_memmove(buffer, temp + 1, ft_strlen(temp + 1) + 1);
			return (ret);
		}
	}
}

int	main(void)
{
	int fd = open("test", O_RDONLY);
	char *line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
}
