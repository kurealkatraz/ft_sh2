/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 16:38:24 by mgras             #+#    #+#             */
/*   Updated: 2015/04/29 16:39:20 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_uscderror(char *err, int mol)
{
	ft_putstr(C_RED);
	if (mol == 000)
	{
		ft_putstr(C_GREEN);
		ft_putstr("WARNING : ");
		ft_putstr(C_BROWN);
		ft_putendl("having multiple path won't help dude");
	}
	else if (mol == 001)
	{
		ft_putstr("ERROR : ");
		ft_putstr(C_CYAN);
		ft_putstr("PWD");
		ft_putstr(C_RED);
		ft_putendl(" was unset or not valid.");
	}
	else if (mol == 002)
	{
		ft_putstr("ERROR : ");
		ft_putstr(C_CYAN);
		ft_putstr(err);
		ft_putstr(C_RED);
		ft_putendl(" is not a valid directory");
	}
	ft_putstr(C_NONE);
}

t_env	*ft_cd_prev(t_lex *med, t_env *env)
{
	char	*join;

	join = NULL;
	if (chdir(ft_get_del_env("OLDPWD", env)->value) != 0)
	{
		ft_uscderror(med->mem, 001);
		return (env);
	}
	else if (med->next->next)
		ft_uscderror(med->mem, 000);
	join = ft_strjoin("OLDPWD=", (ft_get_del_env("PWD", env))->value);
	env = ft_del_env(env, ft_get_del_env("OLDPWD", env));
	env = ft_del_env(env, ft_get_del_env("PWD", env));
	env = ft_new_env(env, join);
	ft_strdel(&join);
	join = ft_strjoin("PWD=", getcwd(NULL, 0));
	env = ft_new_env(env, join);
	ft_strdel(&join);
	return (env);
}

t_env	*ft_cd_usr(t_lex *med, t_env *env)
{
	char	*join;

	join = NULL;
	if (chdir(med->next->mem) != 0)
	{
		ft_uscderror(med->next->mem, 002);
		return (env);
	}
	ft_strdel(&join);
	join = ft_strjoin("OLDPWD=", (ft_get_del_env("PWD", env))->value);
	env = ft_del_env(env, ft_get_del_env("OLDPWD", env));
	env = ft_del_env(env, ft_get_del_env("PWD", env));
	env = ft_new_env(env, join);
	ft_strdel(&join);
	join = ft_strjoin("PWD=", getcwd(NULL, 0));
	env = ft_new_env(env, join);
	ft_strdel(&join);
	return (env);
}

t_env	*ft_cd(t_lex *med, t_env *env)
{
	t_lex	*swp;

	swp = med;
	if (ft_strcmp(swp->next->mem, "-") == 0)
		return (env = ft_cd_prev(swp, env));
	else if (swp->next->next)
		ft_uscderror(NULL, 000);
	else
		return (env = ft_cd_usr(swp, env));
	return (env);
}
