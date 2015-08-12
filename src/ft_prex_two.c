/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prex_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/12 12:14:12 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 12:14:29 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lex	*ft_next_op(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (swp != NULL && !ft_iscompl(swp->mem[0]))
		swp = swp->next;
	if (swp)
		if (ft_iscompl(swp->mem[0]))
			swp = swp->next;
	return (swp);
}

void	ft_exec(char **envp, char **argv, char *bin)
{
	pid_t	child;
	int		sys;

	child = fork();
	if (child == 0)
	{
		execve(bin, argv, envp);
		kill(getpid(), SIGKILL);
	}
	else
		wait(&sys);
	ft_del_exec(&bin, &argv, &envp);
}

char	*ft_get_redi_dir(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (!ft_isredi(swp->mem[0]) && swp)
		swp = swp->next;
	if (swp->next == NULL || swp == NULL)
	{
		ft_scann_eror(007, NULL);
		kill(getpid(), SIGKILL);
	}
	return (swp->next->mem);
}

char	*ft_get_redi(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (!ft_isredi(swp->mem[0]) && swp)
		swp = swp->next;
	if (swp->next == NULL || swp == NULL)
	{
		ft_scann_eror(007, NULL);
		kill(getpid(), SIGKILL);
	}
	return (swp->mem);
}

void	ft_mkfile(char *filename)
{
	pid_t	child;
	int		sys;
	char	**argv;

	child = fork();
	argv = NULL;
	if (child == 0)
	{
		argv = (char**)malloc(sizeof(char*) * 3);
		argv[2] = NULL;
		argv[1] = (char*)malloc(sizeof(char) * ft_strlen(filename) + 1);
		argv[0] = (char*)malloc(sizeof(char) * ft_strlen("touch") + 1);
		ft_strcpy(argv[1], filename);
		ft_strcpy(argv[0], "touch");
		execve("/usr/bin/touch", argv, NULL);
		kill(getpid(), SIGKILL);
	}
	wait(&sys);
}
