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

char	**ft_make_pipe_argv(t_lex *med, t_lex *added)
{
	char		**argv;
	t_lex		*swp;
	int			len;

	len = ft_is_what_len_pipe(med) + ft_is_what_len(added);
	swp = med;
	argv = (char**)malloc(sizeof(char*) * (len));
	argv[len] = NULL;
	while (swp != NULL && !ft_iscompl(swp->mem[0]))
	{
		argv[len] = (char*)malloc(sizeof(char) * ft_strlen(swp->mem) + 1);
		argv[len] = ft_strcpy(argv[len], swp->mem);
		argv[++len] = NULL;
		swp = swp->next;
	}
	swp = added;
	while (swp != NULL)
	{
		argv[len] = (char*)malloc(sizeof(char) * ft_strlen(swp->mem) + 1);
		argv[len] = ft_strcpy(argv[len], swp->mem);
		argv[++len] = NULL;
		swp = swp->next;
	}
	return (argv);
}

char	**ft_del_tab(char **argv)
{
	int		ss;

	ss = 0;
	while (argv[ss] != NULL)
		ft_strdel(&argv[ss++]);
	return (NULL);
}

t_lex	*ft_get_end_of_pipe(int	fd)
{
	char	*line;
	t_lex	*swp;
	t_lex	*added;

	added = NULL;
	while (1 == ft_get_next_line(fd, &line))
	{
		ft_putendl(line);
		added = ft_new_meme(added, line);
	}
	swp = added;
	while (swp)
	{
		ft_putendl(swp->mem);
		swp = swp->next;
	}
	added = ft_rev_lex(added);
	swp = added;
	return (added);
}

t_lex	*ft_chain_pipe_it(t_lex *med, t_env *env, int src)
{
	t_lex	*added;
	t_lex	*swp;
	char	**argv;

	swp = med;
	env = env + 0;
	added = ft_get_end_of_pipe(src);
	swp = med;
	argv = ft_make_pipe_argv(swp, added);
	argv = ft_del_tab(argv);
	return (med);
}

t_lex	*ft_pipe_it(t_lex *med, t_env *env)
{
	int		sys;
	int		fd[2];
	pid_t	child;
	t_lex	*swp;

	pipe(fd);
	swp = med;
	child = fork();
	if (child == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ft_exec(ft_get_envp(env), ft_make_argv(swp), ft_make_bin(med));
		kill(getpid(), SIGKILL);
	}
	else
	{
		close(fd[1]);
		wait(&sys);
		if (ft_is_next_op_pipe(ft_get_next_op(swp)))
		{
			swp = ft_get_next_op(swp);
			swp = ft_chain_pipe_it(swp, env, fd[0]);
		}
	}
	return (med);
}
