/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prex_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/12 12:15:18 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 12:15:44 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_delfile(char *filename)
{
	pid_t	child;
	int		sys;
	char	**argv;

	child = fork();
	argv = NULL;
	if (child == 0)
	{
		argv = (char**)malloc(sizeof(char*) * 4);
		argv[3] = NULL;
		argv[2] = (char*)malloc(sizeof(char) * ft_strlen(filename) + 1);
		argv[1] = (char*)malloc(sizeof(char) * ft_strlen("-rf") + 1);
		argv[0] = (char*)malloc(sizeof(char) * ft_strlen("touch") + 1);
		ft_strcpy(argv[2], filename);
		ft_strcpy(argv[1], "-rf");
		ft_strcpy(argv[0], "rm");
		execve("/bin/rm", argv, NULL);
		kill(getpid(), SIGKILL);
	}
	wait(&sys);
}

int		ft_reboot_file(int fd, t_lex *med)
{
	close(fd);
	ft_delfile(ft_get_redi_dir(med));
	ft_mkfile(ft_get_redi_dir(med));
	return (open(ft_get_redi_dir(med), O_RDWR));
}

void	ft_right_s_redi(t_lex *med, t_env *env)
{
	pid_t	child;
	int		sys;
	int		fd;

	child = fork();
	if (child == 0)
	{
		if ((fd = open(ft_get_redi_dir(med), O_WRONLY)) < 0)
		{
			ft_mkfile(ft_get_redi_dir(med));
			if ((fd = open(ft_get_redi_dir(med), O_WRONLY)) < 0)
			{
				ft_scann_eror(006, ft_get_redi_dir(med));
				kill(getpid(), SIGKILL);
			}
		}
		else
			ft_reboot_file(fd, med);
		dup2(fd, 1);
		ft_exec(ft_get_envp(env), ft_make_argv(med), ft_make_bin(med));
		close(fd);
		kill(getpid(), SIGKILL);
	}
	wait(&sys);
}

void	ft_right_d_redi(t_lex *med, t_env *env)
{
	pid_t	child;
	int		sys;
	int		fd;

	child = fork();
	if (child == 0)
	{
		if ((fd = open(ft_get_redi_dir(med), O_WRONLY | O_APPEND)) < 0)
		{
			ft_mkfile(ft_get_redi_dir(med));
			if ((fd = open(ft_get_redi_dir(med), O_WRONLY | O_APPEND)) < 0)
			{
				ft_scann_eror(006, ft_get_redi_dir(med));
				kill(getpid(), SIGKILL);
			}
		}
		dup2(fd, 1);
		ft_exec(ft_get_envp(env), ft_make_argv(med), ft_make_bin(med));
		close(fd);
		kill(getpid(), SIGKILL);
	}
	wait(&sys);
}

int		ft_is_op_redi(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (swp)
	{
		if (ft_isredi(swp->mem[0]))
			return (1);
		swp = swp->next;
	}
	return (0);
}
