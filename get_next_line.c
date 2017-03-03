/*
** get_next_line.c for get_next_line in /home/brihoum_b/tek1/CPE_2016_getnextline
**
** Made by Benjamin BRIHOUM
** Login   <brihoum_b@epitech.net>
**
** Started on  Mon Jan 02 16:38:52 2017 Benjamin BRIHOUM
** Last update Mon Jan 16 11:36:29 2017 Benjamin BRIHOUM
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static char	*my_realloc(char *str, int size)
{
  char		*dump;
  int		ptr;

  ptr = 0;
  if ((dump = malloc(sizeof(char) * size + 1)) == NULL)
    return (NULL);
  while (str[ptr] != '\0')
    {
      dump[ptr] = str[ptr];
      ptr++;
    }
  free(str);
  return (dump);
}

int	autre(char **str, int a)
{
  (*str)[a] = '\0';
  if (((*str) = my_realloc((*str), a + READ_SIZE)) == NULL)
    return (1);
  return (0);
}

char	*error(char *str)
{
  free(str);
  return (NULL);
}

char		*get_next_line(const int fd)
{
  static int	pointeur = 0;
  static char	buff[READ_SIZE];
  static int	reste = 0;
  char		*str;
  int		i;

  i = 0;
  if ((str = malloc(sizeof(char) * (READ_SIZE) + 1)) == NULL)
    return (NULL);
  if (reste == 0 && (reste = read(fd, buff, READ_SIZE)) != 0)
    pointeur = 0;
  if (reste == -1 || reste == 0)
    return (error(str));
  while (buff[pointeur] != '\n' && buff[pointeur] != '\0')
    {
      str[i++] = buff[pointeur++];
      if (--reste == 0 && (reste = read(fd, buff, READ_SIZE)))
	if ((pointeur = autre(&str, i)) == 1)
	    return (NULL);
    }
  str[i] = '\0';
  pointeur++;
  reste--;
  return (str);
}
