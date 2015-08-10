/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 16:42:56 by mgras             #+#    #+#             */
/*   Updated: 2015/08/10 18:03:54 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_fill_holder(int fd)
{
	int		r;
	char	*buf;
	char	*tmp;

	r = 0;
	if (!(buf = (char*)malloc(sizeof(char) * (BUF_SIZE + 1))))
		return (NULL);
	tmp = NULL;
	while ((r = read(fd, (char*)buf, BUF_SIZE)) > 0)
	{
		buf[r] = '\0';
		tmp = ft_strjoin(tmp, buf);
		if (buf[r - 1] == '\n')
		{
			free(buf);
			return (tmp);
		}
	}
	free(buf);
	return (tmp);
}

int		ft_get_next_line(int fd, char **line)
{
	char	*holder;
	int		len;

	len = 0;
	if (NULL == (holder = ft_fill_holder(fd)))
		return (0);
	while (holder[len] != '\n' && holder[len] != '\0')
		len++;
	if (!(*line = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	len = 0;
	while (holder[len] != '\n' && holder[len] != '\0')
	{
		(*line)[len] = holder[len];
		len++;
	}
	(*line)[len] = '\0';
	return (1);
}
