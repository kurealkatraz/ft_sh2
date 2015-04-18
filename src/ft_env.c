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

	mwp = med;
	ewp = env;
	while (mwp != NULL && !ft_isocmpl(mwp->mem))
	{
		if (ft_strcmp(mwp->mem, "-i") == 0 && ewp == env)
			ewp = NULL;
		else if (ft_check_env(mwp->mem) == 1)
			ewp = ft_new_env(ewp, mwp->mem);
		else
			ft_sann_eror(100, mwp->mem);
		mwp = mwp->next;
	}
	return (ewp);
}

t_env	*ft_free_one_env(t_env	*env)
{
	t_env	*swp;

	free(env->name);
	free(env->value);
	swp = env->next;
	free(env);
	return (swp);
}

t_env	*ft_free_usr_env(t_env *env, t_lex *med)
{
	int		free_len;
	t_lex	*mwp;

	mwp = med;
	free_len = 0;
	while (mwp != NULL && !ft_isocmpl(mwp->mem))
	{
		if (ft_strcmp(mwp->mem, "-i") == 0 && ewp == env)
			free_len = free_len + 0;
		else if (ft_check_env(mwp->mem) == 1)
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
	swp = ft_free_usr_env(swp, med);	//!\ BETTER WATCH OUT M9 /!\\
}

int		ft_lex_env(t_lex *med)
{
	int		pos;
	int		equal;

	pos = 0;
	equal = 0;
	while (med->mem[pos])
	{
		if (pos == 0 && mwp->mem[pos] == '=')
		{
			ft_scann_eror(101, mwp->mem);
			return (-1);
		}
		else if (mwp->mem[pos] == '=' && med->mem[pos + 1] == '\0')
		{
			ft_scann_eror(102, mwp->mem);
			return (-1);
		}
		if (mwp->mem[pos] == '=')
			equal = 1;
	}
	if (equal == 1)
		return (1);
	else
		ft_scann_eror(102, mwp->mem);
	return (-1);
}

int		ft_env_noexec(t_lex *med)
{
	t_lex	*mwp;

	mwp = med;
	while (mwp != NULL && !ft_iscompl(mwp->mem))
	{
		if (!ft_isenvmem(mwp->mem))
			return (0);
	}
	return (0);
}

t_lex	*ft_del_lex_mem(t_lex *prev, t_lex *curr)
{
	if (prev == curr)
	{
		free(prev->mem)
		curr = prev->next;
		free(prev);
		return (curr);
	}
		//WALLLAAAAH
}

int		ft_parse_env(t_lex *med)
{
	t_lex	*mwp;
	t_lex	*save;
	int		change;

	change = 0;
	mwp = med;
	save = mwp;
	while (mwp != NULL && !ft_iscompl(mwp->mem))
	{
		if (ft_lex_env(mwp) == -1)
		{
			mwp = ft_del_lex_mem(save, mwp);
			change++;
		}
		save = mwp;
		mwp = mwp->next;
	}
	if (change == 1)
		ft_commit_env_changes(mwp, change);
	if (mwp == NULL)
		return (2);
	else if (ft_env_noexec(mwp))
		return (1);
	else if (!ft_env_noexec(mwp))
		return (3);
}

t_env	*ft_env(t_lex *med, t_env *env)
{
	t_lex	*swp;

	swp = med;
	if (ft_strcmp(swp->next->mem, "-i") == 0)
	{
		ft_envi(med, env);
		return (env);
	}
	if (ft_parse_env(swp->next) == 1)
		ft_print_env_usr(env, med);
	else if (ft_parse_env(swp->next) == 2)
		ft_print_env(env);
	else if (ft_parse_env(swp->next) == 3)
	{
		swp = ft_make_usr_env(env, med);
		ft_exec(ft_get_envp(swp), ft_make_argv(med->next), ft_make_bin(med->next));
	}
	else
		ft_exec(ft_get_envp(env), ft_make_argv(med->next), ft_make_bin(med->next));
	return (env);
}

t_env	*ft_new_env(t_env *env, char *full)
{
	t_env	*new;
	size_t	size;

	size = 0;
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
