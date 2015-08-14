/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/14 13:11:23 by mgras             #+#    #+#             */
/*   Updated: 2015/08/14 13:22:24 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_d_r_redi_init(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	if (access(ft_get_redi_dir(swp), F_OK) == -1)
		ft_mkfile(ft_get_redi_dir(swp));
	return (open(ft_get_redi_dir(swp), O_RDWR | O_APPEND));
}

int	ft_d_r_redi_p(char **argv, char **envp, t_lex *swp, int fd)
{
	int		sys;
	int		out;
	char	*bin;
	char	*filename;
	pid_t	child;

	out = ft_d_r_redi_init(swp);
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
