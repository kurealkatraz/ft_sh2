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

t_env	*ft_env(t_lex *med, t_env *env)
{
	t_lex	*swp;

	swp = med;
	if (ft_strcmp(swp->next->mem, "-i") == 0)
	{
		ft_envi(med, env);
		return (env);
	}
	if (ft_check_env(swp->next->mem) == 1)
		ft_print_env_usr(env, med);
	else if (ft_check_env(swp->next->mem) == 2)
		ft_print_env(env);
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
