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

/*
** WILL GO IN UTILITY.C
*/

void	ft_del_exec_req(char **bin, char ***argv, char ***envp)
{
	ft_strdel(bin);
	ft_del_tab(*argv);
	ft_del_tab(*envp);
}

void	ft_cre_exec_req(char **b, char ***a, char ***e, t_lex *m, t_env *en)
{
	t_lex	*swp;

	swp = m;
	if (b)
		*b = ft_make_bin(swp);
	if (a)
		*a = ft_make_argv(swp);
	if (e)
		*e = ft_get_envp(en);
}

/*
**	WILL GO IN UTILITY.C
*/

char	**ft_make_pipe_argv(t_lex *med, t_lex *added)
{
	char		**argv;
	t_lex		*swp;
	int			len;
	int			ss;

	len = ft_is_what_len_pipe(med) + ft_is_what_len(added);
	swp = med;
	argv = (char**)malloc(sizeof(char*) * (len));
	argv[len] = NULL;
	ss = 0;
	while (swp != NULL && swp->mem[0] != '|' && ss <= len)
	{
		argv[ss] = (char*)malloc(sizeof(char) * ft_strlen(swp->mem) + 1);
		argv[ss] = ft_strcpy(argv[ss], swp->mem);
		argv[++ss] = NULL;
		swp = swp->next;
	}
	swp = added;
	while (swp != NULL && ss <= len)
	{
		argv[ss] = (char*)malloc(sizeof(char) * ft_strlen(swp->mem) + 1);
		argv[ss] = ft_strcpy(argv[ss], swp->mem);
		argv[++ss] = NULL;
		swp = swp->next;
	}
	ft_free_lex(added);
	return (argv);
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
	return (NULL);
}

t_lex	*ft_get_end_of_pipe(int	fd)
{
	char	*line;
	t_lex	*added;

	added = NULL;
	while (1 == ft_get_file(fd, &line))
		added = ft_new_meme(added, line);
	added = ft_rev_lex(added);
	close(fd);
	return (added);
}

int		ft_pipe_pipes(char *bin, char **argv, char **env)
{
	int		fd[2];
	int		sys;
	pid_t	child;

	child = fork();
	pipe(fd);
	if (child == 0)
	{
		close(fd[1]);
		dup2(fd[1], 1);
		ft_exec(env, argv, bin);
		close(fd[0]);	//must check
		kill(getpid(), SIGKILL);
	}
	else
	{
		wait(&sys);
		close(fd[0]);
	}
	return (fd[1]);
}

t_lex	*ft_pipe_it(t_lex *med, t_env *env)
{
	char	**envp;
	char	**argv;
	char	*bin;
	t_lex	*swp;
	int		fd;

	swp = med;
	fd = 0;
	while (ft_is_next_op_pipe(ft_get_next_op(swp)))
	{
		if (fd == 0)
		{
			ft_cre_exec_req(&bin, &argv, &envp, swp, env);
			fd = ft_pipe_pipes(bin, argv, envp);
		}
		else
		{
			ft_cre_exec_req(&bin, NULL, &envp, swp, env);
			ft_make_pipe_argv(swp, ft_get_end_of_pipe(fd));
			close(fd);
			fd = ft_pipe_pipes(bin, argv, envp);
			ft_del_exec_req(&bin, &argv, &envp);
		}
		ft_get_next_op(swp);
	}
	return (swp);
}
