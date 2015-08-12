/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/12 11:46:42 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 11:46:58 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lex	*ft_get_added(int fd, t_lex *added)
{
	char	*line;

	while (ft_get_file(fd, &line) > 0)
		added = ft_new_meme(added, line);
	return (added = ft_rev_lex(added));
}

char	**ft_make_read(int fd)
{
	t_lex		*added;
	char		**tab;
	int			len;

	added = NULL;
	added = ft_get_added(fd, added);
	len = ft_is_what_len(added);
	tab = (char**)malloc(sizeof(char*) * (len));
	tab[len + 1] = NULL;
	len = 0;
	while (added)
	{
		tab[len++] = ft_strdup(added->mem);
		tab[len] = NULL;
		added = added->next;
	}
	return (tab);
}
