/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_care.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 16:27:44 by mgras             #+#    #+#             */
/*   Updated: 2015/03/25 17:14:53 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_env	*ft_minimal_env_gen(t_env *env)
{
	if (env != NULL)
		env = ft_free_all_env(env);
	env = ft_new_env(env, "PATH=/bin:usr/bin");
	env = ft_new_env(env, ft_strjoin("PWD=", getcwd(NULL, PATH_MAX)));
	env = ft_new_env(env, "_=usr/bin/env");
	return (env);
}

t_env	*ft_env_generator(t_env *env, char **med, int markpos)
{
	int		pos;

	pos = 2;
	env = ft_minimal_env_gen(env);
	while (pos < markpos)
	{
		if (ft_check_setenv(med[pos]) == 1)
			env = ft_new_env(env, med[pos]);
		pos++;
	}
	return (env);
}
