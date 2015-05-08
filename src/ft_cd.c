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

#include "ft_shell.h"

t_env	*ft_cd_prev(t_lex *med, t_env *env)
{
	env = ft_del_env(env, ft_get_del_env("OLDPWD", env));
	return (env);
}

t_env	ft_cd(t_lex *med, t_env *env)
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
