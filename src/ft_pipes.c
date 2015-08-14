/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 18:26:15 by mgras             #+#    #+#             */
/*   Updated: 2015/08/14 13:33:02 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_start_pipe(char **argv, char **envp, char *bin)
{
	int		fd[2];
	int		sys;
	pid_t	child;

	if (bin == NULL)
		ft_scann_eror(04, NULL);
	pipe(fd);
	child = fork();
	if (!child)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execve(bin, argv, envp);
		kill(getpid(), SIGKILL);
	}
	else
	{
		wait(&sys);
		close(fd[1]);
	}
	ft_strdel(&bin);
	return (fd[0]);
}

int		ft_rec_pipe(char **argv, char **envp, char *bin, int src)
{
	int		fd[2];
	int		sys;
	pid_t	child;

	if (bin == NULL)
		ft_scann_eror(04, NULL);
	pipe(fd);
	child = fork();
	if (child == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		dup2(src, 0);
		execve(bin, argv, envp);
		close(src);
		kill(getpid(), SIGKILL);
	}
	else
	{
		wait(&sys);
		close(fd[1]);
	}
	ft_strdel(&bin);
	return (fd[0]);
}

int		ft_end_pipe(char **argv, char **envp, char *bin, int src)
{
	int		sys;
	pid_t	child;

	if (bin == NULL)
		ft_scann_eror(04, NULL);
	child = fork();
	if (child == 0)
	{
		dup2(src, 0);
		execve(bin, argv, envp);
		close(src);
		kill(getpid(), SIGKILL);
	}
	else
		wait(&sys);
	ft_strdel(&bin);
	return (-2);
}

int		ft_cont_redi(t_lex *med)
{
	t_lex *swp;

	swp = med;
	while (swp)
	{
		if (swp->mem[0] == '>')
			return (1);
		swp = swp->next;
	}
	return (0);
}

t_lex	*ft_pipe_it(t_lex *med, t_env *env, int fd)
{
	t_lex	*swp;
	char	**envp;
	char	**argv;

	swp = med;
	envp = NULL;
	envp = ft_get_envp(env);
	argv = ft_make_argv(swp);
	if (fd < 2)
		fd = ft_start_pipe(argv, envp, ft_make_bin(swp));
	else if (ft_is_next_op_pipe(swp))
		fd = ft_rec_pipe(argv, envp, ft_make_bin(swp), fd);
	else
		fd = ft_final_output(argv, envp, swp, fd);
	ft_del_tab(argv);
	ft_del_tab(envp);
	if (ft_is_next_op_pipe(swp))
		swp = ft_pipe_it(ft_get_next_op(swp), env, fd);
	return (NULL);
}
