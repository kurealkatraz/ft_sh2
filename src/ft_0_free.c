/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_0_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 10:53:54 by mgras             #+#    #+#             */
/*   Updated: 2015/03/25 17:05:18 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_free_argv(char **argv)
{
	int		ts;

	ts = 0;
	while (argv[ts] != NULL)
	{
		argv[ts] = NULL;
		free(argv[ts++]);
	}
	free(argv);
	argv = NULL;
}

t_env	*ft_free_member(t_env *current, t_env *saved)
{
	free(current->name);
	free(current->value);
	if (saved != NULL)
		saved->next = current->next;
	else
	{
		saved = current->next;
		free(current);
		return (saved);
	}
	free(current);
	return (saved->next);
}

t_env	*ft_free_all_env(t_env *env)
{
	t_env	*swp;

	swp = env;
	while (env != NULL)
	{
		swp = env;
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		env = env->next;
		free(swp);
	}
	return (NULL);
}
