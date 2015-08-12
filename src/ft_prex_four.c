/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prex_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/12 12:16:07 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 12:16:18 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lex	*ft_get_next_op(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	if (med == NULL)
		return (med);
	{
		while (!ft_iscompl(swp->mem[0]))
		{
			if (swp == NULL)
				return (swp);
			swp = swp->next;
			if (swp == NULL)
				return (swp);
		}
	}
	return (swp->next);
}

t_env	*ft_what_buildtin(t_lex *med, t_env *env)
{
	if (ft_strcmp(med->mem, "env") == 0)
		env = ft_env(med, env);
	else if (ft_strcmp(med->mem, "setenv") == 0)
		env = ft_setenv(med, env);
	else if (ft_strcmp(med->mem, "unsetenv") == 0)
		env = ft_unsetenv(med, env);
	else if (ft_strcmp(med->mem, "cd") == 0)
		env = ft_cd(med, env);
	return (env);
}

char	**ft_cre_exec(char **bin, char ***argv, t_lex *med, t_env *env)
{
	t_lex		*swp;

	swp = med;
	if (bin)
		*bin = ft_make_bin(swp);
	if (argv)
		*argv = ft_make_argv(swp);
	return (ft_get_envp(env));
}

void	ft_del_exec(char **bin, char ***argv, char ***envp)
{
	if (bin)
		ft_strdel(bin);
	if (argv)
		ft_del_tab(*argv);
	if (envp)
		ft_del_tab(*envp);
}

t_lex	*ft_get_fd_s_redi(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (swp && swp->mem[0] != '<' && swp->mem[1] != '\0')
		swp = swp->next;
	return (swp->next);
}
