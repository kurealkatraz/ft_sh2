/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/12 11:46:42 by mgras             #+#    #+#             */
/*   Updated: 2015/08/14 13:39:23 by mgras            ###   ########.fr       */
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

int		ft_s_r_redi_init(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	ft_delfile(ft_get_redi_dir(swp));
	ft_mkfile(ft_get_redi_dir(swp));
	return (open(ft_get_redi_dir(swp), O_RDWR));
}

int		ft_s_r_redi_p(char **argv, char **envp, t_lex *swp, int fd)
{
	int		sys;
	int		out;
	char	*bin;
	char	*filename;
	pid_t	child;

	out = ft_s_r_redi_init(swp);
	child = fork();
	if (child == 0)
	{
		bin = ft_make_bin(swp);
		filename = ft_get_redi_dir(swp);
		dup2(fd, 0);
		dup2(out, 1);
		execve(bin, argv, envp);
		close(fd);
		close(out);
		ft_strdel(&bin);
		ft_strdel(&filename);
		kill(getpid(), SIGKILL);
	}
	wait(&sys);
	return (out);
}
