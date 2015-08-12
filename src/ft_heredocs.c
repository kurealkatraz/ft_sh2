/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/04 18:23:09 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 12:52:01 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_top_kek(t_lex *med, t_env *env)
{
	pid_t	child;
	char	**argv;
	char	**envp;
	char	*bin;
	int		sys;

	child = fork();
	if (!child)
	{
		envp = ft_cre_exec(&bin, &argv, med, env);
		dup2(open("/tmp/minishell_here_stock", O_RDWR), 0);
		execve(bin, argv, envp);
		ft_del_exec(&bin, &argv, &envp);
	}
	else
		wait(&sys);
}

void	ft_print_here(t_lex *here, t_lex *med, t_env *env)
{
	t_lex		*h_swp;
	int			len;
	char		*f_line;

	h_swp = here;
	while (h_swp)
	{
		len = len + 1 + ft_strlen(h_swp->mem);
		h_swp = h_swp->next;
	}
	f_line = (char*)malloc(sizeof(char) * (len + 1));
	h_swp = here;
	while (h_swp)
	{
		ft_strcat(f_line, h_swp->mem);
		ft_strcat(f_line, "\n");
		h_swp = h_swp->next;
	}
	f_line[len + 1] = '\0';
	ft_nice_meme(f_line);
	ft_strdel(&f_line);
	ft_top_kek(med, env);
}

void	ft_left_d_redi(t_lex *med, t_lex *curr, t_env *env)
{
	t_lex	*here_store;
	t_lex	*h_swp;

	here_store = ft_solo_heredocs(curr);
	h_swp = here_store;
	curr = ft_get_here(med);
	if (curr == med)
		while (h_swp)
		{
			ft_putendl(h_swp->mem);
			h_swp = h_swp->next;
		}
	else
		ft_print_here(h_swp, med, env);
	ft_free_lex(here_store);
}
