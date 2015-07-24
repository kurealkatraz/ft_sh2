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

t_lex	*ft_get_end_of_pipe(int	fd)
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

/*
**	WILL GO IN UTILITY.C
*/

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
	len = ft_is_what_len(added = ft_get_added(fd, added));
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

int			ft_start_pipe(char **argv, char **envp, char *bin)
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

int			ft_rec_pipe(char **argv, char **envp, char *bin, int src)
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

t_lex		*ft_pipe_it(t_lex *med, t_env *env, int fd)
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
		fd = ft_end_pipe(argv, envp, ft_make_bin(swp), fd);
	ft_del_tab(argv);
	ft_del_tab(envp);
	if (ft_is_next_op_pipe(swp))
		swp = ft_pipe_it(ft_get_next_op(swp), env, fd);
	return (swp);
}
