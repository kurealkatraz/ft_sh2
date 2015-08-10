/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 23:19:34 by mgras             #+#    #+#             */
/*   Updated: 2015/08/10 23:24:16 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_print_env(t_env *env)
{
	t_env	*swp;

	swp = env;
	while (swp != NULL)
	{
		ft_putstr(swp->name);
		ft_putchar('=');
		ft_putendl(swp->value);
		swp = swp->next;
	}
}

t_env	*ft_make_usr_env(t_env *env, t_lex *med)
{
	t_env	*ewp;
	t_lex	*mwp;

	mwp = med->next;
	ewp = env;
	while (mwp != NULL && !ft_iscompl(mwp->mem[0]))
	{
		if (ft_strcmp(mwp->mem, "-i") == 0 && ewp == env)
			ewp = NULL;
		else if (ft_lex_env(mwp) == 1)
			ewp = ft_new_env(ewp, mwp->mem);
		else
			ft_scann_eror(100, mwp->mem);
		mwp = mwp->next;
	}
	return (ewp);
}

t_env	*ft_free_usr_env(t_env *env, t_lex *med)
{
	int		free_len;
	t_lex	*mwp;

	mwp = med;
	free_len = 0;
	while (mwp != NULL && !ft_iscompl(mwp->mem[0]))
	{
		if (ft_strcmp(mwp->mem, "-i") == 0)
			free_len = free_len + 0;
		else if (ft_lex_env(mwp) == 1)
			free_len++;
		else
			free_len = free_len + 0;
		mwp = mwp->next;
	}
	while (free_len > 0)
	{
		env = ft_free_one_env(env);
		free_len--;
	}
	return (env);
}

void	ft_print_env_usr(t_env *env, t_lex *med)
{
	t_env	*swp;

	swp = ft_make_usr_env(env, med);
	ft_print_env(swp);
	swp = ft_free_usr_env(swp, med);
}

int		ft_lex_env(t_lex *med)
{
	int		pos;
	int		equal;
	t_lex	*mwp;

	pos = 0;
	equal = 0;
	mwp = med;
	if (mwp == NULL)
		return (1);
	if (ft_is_buildtin(mwp->mem) || mwp->path != NULL)
		return (2);
	while (mwp->mem[pos])
	{
		if (pos == 0 && mwp->mem[pos] == '=')
			return (-1);
		if (mwp->mem[pos] == '=')
			equal++;
		pos++;
	}
	if (equal == 1)
		if (ft_is_dubs(mwp))
			return (-1);
	if (equal == 1 && med->mem[pos - 1] != '=')
		return (1);
	return (-1);
}
