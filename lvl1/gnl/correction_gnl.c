#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
  int i = 0;
  // CORRECTION 1 : Protection si la chaîne est vide ou si 'c' n'est pas trouvé avant le '\0'
  while(s && s[i] != '\0' && s[i] != c)
    i++;
  if (s && s[i] == c)
    return s + i;
  else
    return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
  // CORRECTION 2 : Correction des index (on va de 0 à n-1)
  size_t i = 0;
  while(i < n)
  {
    ((char *)dest)[i] = ((char *)src)[i];
    i++;
  }
  return dest;
}

size_t ft_strlen(char *s)
{
  size_t res = 0;
  if (!s) return 0; // CORRECTION 3 : Sécurité si s est NULL
  while (*s)
  {
    s++;
    res++;
  }
  return res;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
  size_t size1 = ft_strlen(*s1);
  char *tmp = malloc(size2 + size1 + 1);
  if (!tmp)
    return 0;
  if (size1 > 0) ft_memcpy(tmp, *s1, size1);
  ft_memcpy(tmp + size1, s2, size2);
  tmp[size1 + size2] = '\0';
  free(*s1);
  *s1 = tmp;
  return 1;
}

int str_append_str(char **s1, char *s2)
{
  return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
  // CORRECTION 4 : Suppression de la récursion infinie et de la dépendance à ft_strlen
  char *d = dest;
  const char *s = src;

  if (d < s)
  {
    for (size_t i = 0; i < n; i++)
      d[i] = s[i];
  }
  else if (d > s)
  {
    for (size_t i = n; i > 0; i--)
      d[i - 1] = s[i - 1];
  }
  return dest;
}

char *get_next_line(int fd)
{
  static char b[BUFFER_SIZE + 1] = "";
  char *ret = NULL;

  // CORRECTION 5 : Initialisation indispensable pour ft_strlen(*s1) au premier tour
  ret = malloc(1);
  if (!ret) return NULL;
  ret[0] = '\0';

  char *tmp = ft_strchr(b, '\n');
  while(!tmp)
  {
    if (!str_append_str(&ret, b))
      return (NULL);
    int read_ret = read(fd, b, BUFFER_SIZE);
    if (read_ret == -1 || read_ret == 0) // CORRECTION 6 : Gestion de la fin de fichier (EOF) ou erreur
    {
      if (read_ret == 0 && ft_strlen(ret) > 0) break; // Renvoie ce qu'il reste
      free(ret);
      return (NULL);
    }
    b[read_ret] = 0;
    tmp = ft_strchr(b, '\n'); // CORRECTION 7 : Mise à jour indispensable pour ne pas boucler à l'infini !
  }

  if (tmp)
  {
    if (!str_append_mem(&ret, b, tmp - b + 1))
    {
      free(ret);
      return NULL;
    }
    // CORRECTION 8 : Décalage du buffer pour le prochain appel de GNL
    ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
  }

  return ret;
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
