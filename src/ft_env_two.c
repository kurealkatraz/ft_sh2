/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 23:24:50 by mgras             #+#    #+#             */
/*   Updated: 2015/08/10 23:27:53 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lex	*ft_get_exec(t_lex *med)
{
	t_lex	*mwp;

	mwp = med;
	while (mwp && !ft_ispath(mwp->mem))
		mwp = mwp->next;
	if (mwp != NULL)
		return (mwp);
	mwp = med;
	while (mwp && !mwp->path && ft_strcmp(mwp->mem, "env") != 0)
		mwp = mwp->next;
	return (mwp);
}

t_env	*ft_env(t_lex *med, t_env *env)
{
	t_lex	*swp;
	t_env	*ewp;
	int		pars;

	swp = med;
	ewp = env;
	if (swp->next)
		if (ft_strcmp(swp->next->mem, "-i") == 0)
		{
			ft_del_lex_mem(med, med->next);
			return (ft_env(med, NULL));
		}
	pars = ft_parse_env(swp, 0, 0);
	if (pars == 1)
		ft_print_env_usr(env, med);
	else if (pars == 2)
		ft_print_env(env);
	else if (pars == 3)
		ft_exec(ft_get_envp(ewp = ft_make_usr_env(ewp, med)),\
		ft_make_argv(ft_get_exec(med)), ft_make_bin(ft_get_exec(med)));
	else
		ft_exec(ft_get_envp(ewp), ft_make_argv(ft_get_exec(med)),\
		ft_make_bin(ft_get_exec(med)));
	return (env);
}

void	ft_commit_env_changes(t_lex *med, int nb)
{
	t_lex	*swp;

	swp = med;
	ft_putstr(C_RED);
	ft_putstr("[WARNING]: ");
	ft_putstr(C_CYAN);
	ft_putnbr(nb);
	ft_putendl(" unvalid entr(ies)/(y) have been found.");
	ft_putendl("This is how the command was corrected");
	ft_putstr(C_MAGENTA);
	while (swp != NULL && !ft_iscompl(swp->mem[0]))
	{
		ft_putstr(swp->mem);
		ft_putchar(' ');
		swp = swp->next;
	}
	ft_putchar('\n');
	ft_putstr(C_NONE);
}

int		ft_ret_parse_env(int change, t_lex *med)
{
	if (change > 0)
		ft_commit_env_changes(med, change);
	if (med->next == NULL)
		return (2);
	else if (ft_env_noexec(med))
		return (1);
	else if (!ft_env_noexec(med))
		return (3);
	return (0);
}

int		ft_parse_env(t_lex *med, int change, int index)
{
	t_lex	*mwp;
	t_lex	*save;

	mwp = med->next;
	save = med;
	while (mwp != NULL && !ft_iscompl(mwp->mem[0]))
	{
		index = ft_lex_env(mwp);
		if (index == -1 && mwp->path == NULL && !ft_ispath(mwp->mem))
		{
			mwp = ft_del_lex_mem(save, mwp);
			if (mwp == med)
				mwp = med->next;
			change++;
		}
		else if (index == 2)
			while (mwp != NULL && !ft_iscompl(mwp->mem[0]))
				mwp = mwp->next;
		else
		{
			save = mwp;
			mwp = mwp->next;
		}
	}
	return (ft_ret_parse_env(change, med));
}
