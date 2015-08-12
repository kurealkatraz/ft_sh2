/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/12 11:43:07 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 11:44:31 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lex	*ft_print_lex(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (swp != NULL)
	{
		ft_putendl(swp->mem);
		swp = swp->next;
	}
	return (med);
}

char	**ft_del_tab(char **argv)
{
	int		ss;

	ss = 0;
	if (!argv)
		return (NULL);
	while (argv[ss] != NULL)
	{
		ft_strdel(&argv[ss]);
		ss++;
	}
	return (argv);
}

t_lex	*ft_get_end_of_pipe(int fd)
{
	char	*line;
	t_lex	*added;

	added = NULL;
	while (0 > ft_get_file(fd, &line))
	{
		if (line)
			added = ft_new_meme(added, line);
	}
	added = ft_rev_lex(added);
	close(fd);
	return (added);
}

char	**ft_print_raw_tab_fd(char **tab, int fd)
{
	int		ss;

	ss = 0;
	while (tab[ss])
		ft_putstr_fd(tab[ss++], fd);
	return (tab);
}

char	**ft_print_tab(char **tab)
{
	int		ss;

	ss = 0;
	while (tab[ss])
		ft_putendl(tab[ss++]);
	return (tab);
}
