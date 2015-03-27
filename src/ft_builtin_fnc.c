/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_fnc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 14:42:02 by mgras             #+#    #+#             */
/*   Updated: 2015/03/25 16:51:58 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_env	*ft_setenv(t_env *env, char *mod)
{
	t_env	*swap;
	char	*name;
	int		len;

	swap = env;
	len = 0;
	while (mod[len] != '=' && mod[len] != '\0')
		len++;
	name = (char*)malloc(sizeof(char) * (len + 1));
	name = ft_strncpy(name, mod, len);
	while (swap != NULL)
	{
		if (0 == ft_strcmp(name, swap->name))
		{
			env = ft_unsetenv(env, name);
			env = ft_setenv(env, mod);
		}
		else if (swap->next == NULL)
			env = ft_new_env(env, mod);
		swap = swap->next;
	}
	free(name);
	return (env);
}

t_env	*ft_unsetenv(t_env *env, char *mod)
{
	t_env	*tmp;
	t_env	*save;
	int		r;

	tmp = env;
	save = env;
	r = 42;
	if ((r = ft_strcmp(tmp->name, mod)) != 0)
		tmp = tmp->next;
	else
	{
		env = env->next;
		ft_free_member(tmp, NULL);
		return (env);
	}
	while ((r = ft_strcmp(tmp->name, mod)) != 0 && tmp->next != NULL)
	{
		save = tmp;
		tmp = tmp->next;
	}
	if (r != 0)
		e_no_match_env(mod);
	else
		tmp = ft_free_member(tmp, save);
	return (env);
}

t_env	*ft_oldpwd(t_env *env)
{
	t_env	*swp;

	swp = env;
	while (ft_strcmp(swp->name, "OLDPWD") != 0 && swp->next != NULL)
		swp = swp->next;
	return (env = ft_cd(env, swp->value));
}

t_env	*ft_cd(t_env *env, char *dir)
{
	int		r;

	if (dir == NULL)
		return (ft_home_cd(env));
	if (dir[0] == '-')
		return (env = ft_oldpwd(env));
	if ((r = chdir(dir)) != 0)
	{
		ft_putstr(dir);
		ft_putstr(" is not a Valid Directory\n");
	}
	if (r == 0)
		env = ft_maj_old(env);
	env = ft_maj_pwd(env);
	return (env);
}
