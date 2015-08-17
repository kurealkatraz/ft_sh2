/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_maker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/07 15:49:55 by mgras             #+#    #+#             */
/*   Updated: 2015/08/10 18:12:21 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_split_path(char *value)
{
	char	*path;
	int		i;

	i = 0;
	while (value[i] != '\0' && value[i] != ':')
		i++;
	path = (char*)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (value[i] != '\0' && value[i] != ':')
	{
		path[i] = value[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

t_pth	*ft_new_pth(t_pth *pth, char *path)
{
	t_pth	*newpth;
	int		i;

	i = 0;
	newpth = (t_pth*)malloc(sizeof(t_pth));
	newpth->next = pth;
	while (path[i] != '\0')
		i++;
	newpth->path = (char*)malloc(sizeof(char) * (i + 1));
	i = 0;
	newpth->path = ft_strcpy(newpth->path, path);
	newpth->next = pth;
	ft_strdel(&path);
	return (newpth);
}

t_pth	*ft_get_pth(t_pth *pth, t_env *env)
{
	t_env	*swap;
	int		i;

	i = 0;
	swap = env;
	while (swap != NULL && 0 != ft_strcmp(swap->name, "PATH"))
		swap = swap->next;
	if (swap == NULL)
		return (NULL);
	while (swap->value[i] != '\0')
	{
		pth = ft_new_pth(pth, ft_split_path(swap->value + i));
		i = i + ft_strlen(pth->path) + 1;
	}
	return (pth);
}

void	ft_free_pth(t_pth *pth)
{
	t_pth	*save;

	while (pth != NULL)
	{
		save = pth;
		pth = pth->next;
		free(save->path);
		free(save);
	}
	save = NULL;
	pth = NULL;
}
