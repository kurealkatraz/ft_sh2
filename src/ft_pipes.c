/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 18:26:15 by mgras             #+#    #+#             */
/*   Updated: 2015/04/05 14:20:27 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lex	*ft_parse_pipe(t_lex *med, t_env *env)
{
	
}

t_lex	*ft_pipe_it(t_lex *med, t_env *env)
{
	int		sys;
	int		pipe[2];
	pid_t	child;

	pipe(fd);
	child = fork();
	if (child == 0)
	{
		close(fd[0]);
		dup2(1, fd[0]);
		kill(getpid(), SIGKILL);
	}
	else
	{
		close(fd[1]);
		wait(&sys);
		med = ft_get_next_op(med);
		//parsing needed;
	}
	return (med);
}
