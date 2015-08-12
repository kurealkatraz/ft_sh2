/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/12 11:39:03 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 11:42:05 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lex	*ft_get_here(t_lex *med)
{
	t_lex *swp;

	swp = med;
	while (!ft_isredi(swp->mem[0]))
		swp = swp->next;
	return (swp->next);
}

t_lex	*ft_solo_heredocs(t_lex *med)
{
	char	*line;
	t_lex	*here;
	t_lex	*swp;

	here = NULL;
	swp = ft_get_here(med);
	ft_putstr("NOTheredocs>");
	ft_get_next_line(0, &line);
	while (ft_strcmp(swp->mem, line))
	{
		ft_putstr("NOTheredocs>");
		ft_get_next_line(0, &line);
		if (ft_strcmp(med->mem, line))
			here = ft_new_meme(here, line);
	}
	return (here);
}

void	ft_nice_meme(char *f_line)
{
	int		fd;

	ft_mkfile("/tmp/minishell_here_stock");
	fd = open("/tmp/minishell_here_stock", O_RDWR);
	ft_putstr_fd(f_line, fd);
	close(fd);
}
