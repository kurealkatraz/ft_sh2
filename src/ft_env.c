/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/31 17:50:49 by mgras             #+#    #+#             */
/*   Updated: 2015/03/31 17:51:11 by mgras            ###   ########.fr       */
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
	swp = ft_free_usr_env(swp, med);	//!\ BETTER WATCH OUT M9
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

int		ft_env_noexec(t_lex *med)
{
	t_lex	*mwp;

	mwp = med;
	while (mwp != NULL && !ft_iscompl(mwp->mem[0]))
	{
		if (mwp->path != NULL && !ft_is_buildtin(mwp->mem))
			return (0);
		mwp = mwp->next;
	}
	return (1);
}

t_lex	*ft_del_lex_mem(t_lex *prev, t_lex *curr)
{
	if (prev == curr)
	{
		free(prev->mem);
		curr = prev->next;
		free(prev);
		return (curr);
	}
	prev->next = curr->next;
	free(curr->mem);
	free(curr);
	return (prev);
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

int		ft_parse_env(t_lex *med)
{
	t_lex	*mwp;
	t_lex	*save;
	int		change;
	int		index;

	change = 0;
	index = 0;
	mwp = med->next;
	save = med;
	while (mwp != NULL && !ft_iscompl(mwp->mem[0]))
	{
		index = ft_lex_env(mwp);
		if (index == -1 && mwp->path == NULL)
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

t_lex	*ft_get_exec(t_lex *med)
{
	t_lex	*mwp;

	mwp = med;
	while (mwp->path == NULL)
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
	pars = 0;
	if (swp->next)
		if (ft_strcmp(swp->next->mem, "-i") == 0)
		{
			ft_del_lex_mem(med, med->next);
			ft_env(med, NULL);
			return (env);
		}
	pars = ft_parse_env(swp);
	if (pars == 1)
		ft_print_env_usr(env, med);
	else if (pars == 2)
		ft_print_env(env);
	else if (pars == 3)
	{
		ewp = ft_make_usr_env(ewp, med);
		ft_exec(ft_get_envp(ewp), ft_make_argv(ft_get_exec(med)), ft_make_bin(ft_get_exec(med)));	//must do path compability
	}
	else
		ft_exec(ft_get_envp(ewp), ft_make_argv(ft_get_exec(med)), ft_make_bin(ft_get_exec(med)));	//must do path compability
	return (env);
}

t_env	*ft_free_one_env(t_env	*env)
{
	t_env	*swp;

	swp = env->next;
	free(env->name);
	free(env->value);
	free(env);
	return (swp);
}

t_env	*ft_del_env(t_env *env, t_env *del)
{
	t_env	*swp;

	swp = env;
	if (del == NULL)
		return (env);
	if (del == env)
	{
		env = ft_free_one_env(env);
		return (env);
	}
	while (swp->next != del)
		swp = swp->next;
	swp->next = ft_free_one_env(del);
	return (env);
}

t_env	*ft_new_env(t_env *env, char *full)
{
	t_env	*new;
	size_t	size;

	size = 0;
	new = NULL;
	if (full == NULL)
		return (env);
	while (full[size] != '\0' && full[size] != '=')
		size++;
	new = (t_env*)malloc(sizeof(t_env));
	new->next = env;
	new->name = (char*)malloc(sizeof(char) * (size + 1));
	new->name = ft_strncpy(new->name, full, size);
	new->value = ft_strsub(full, size + 1, (ft_strlen(full) - size));
	return (new);
}

t_env	*ft_get_env(t_env *env, char **envp)
{
	int		ts;

	ts = 0;
	while (envp[ts + 1] != NULL)
		ts++;
	while (ts >= 0)
		env = ft_new_env(env, envp[ts--]);
	return (env);
}
