/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/08 10:28:14 by mgras             #+#    #+#             */
/*   Updated: 2015/07/08 10:28:16 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		error(char **holder)
{
  *holder = NULL;
  return (-1);
}

int   ft_get_file(const int fd, char **line)
{
  static char		*holder;
  char			*buff;
  ssize_t			r;

  if (fd < 0 || BUFF_SIZE > 1000000000 || !(line))
    return (error(&holder));
  if (!(holder))
  {
    if (!(holder = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))) ||
        !(buff = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
      return (error(&holder));
    while ((r = read(fd, buff, BUFF_SIZE)) > 0)
    {
      buff[r] = '\0';
      holder = ft_strjoin(holder, buff);
    }
    if (r == -1)
      return (error(&holder));
  }
  *line = ft_strcdup(holder, '\n');
  holder += ft_strlen(*line);
  if (*holder++ == '\0')
    return (1 + error(&holder));
  return (1);
}
