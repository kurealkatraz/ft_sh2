/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utility.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 16:48:26 by mgras             #+#    #+#             */
/*   Updated: 2015/03/25 17:14:34 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_is_builtin(char *name)
{
	if (0 == ft_strcmp(name, "exit"))
		exit(0);
	else if (0 == ft_strcmp(name, "cd"))
		return (1);
	else if (0 == ft_strcmp(name, "env"))
		return (1);
	else if (0 == ft_strcmp(name, "setenv"))
		return (1);
	else if (0 == ft_strcmp(name, "unsetenv"))
		return (1);
	return (0);
}

t_env	*ft_builtin(char **argv, t_env *env)
{
	if (0 == ft_strcmp(argv[0], "cd") && argv[1] != NULL)
	{
		if (argv[2])
		{
			ft_cd_errors(2, NULL);
			return (env);
		}
		env = ft_maj_pwd(env);
		return (ft_cd(env, argv[1]));
	}
	else if (0 == ft_strcmp(argv[0], "cd") && argv[1] == NULL)
		return (ft_cd(env, NULL));
	else if (0 == ft_strcmp(argv[0], "env"))
		return (ft_builtin_env(argv, env));
	else if (0 == ft_strcmp(argv[0], "setenv") && argv[1] != NULL)
	{
		if (ft_check_setenv(argv[1]) == 1)
			return (ft_setenv(env, argv[1]));
	}
	else if (0 == ft_strcmp(argv[0], "unsetenv") && argv[1] != NULL)
		return (ft_unsetenv(env, argv[1]));
	return (env);
}

t_env	*ft_builtin_env(char **argv, t_env *env)
{
	t_env	*swap;

	swap = env;
	if (argv[1])
	{
		if (!(argv[2]))
			return (env);
		if (0 == ft_strcmp(argv[1], "-i"))
			return (ft_env_i(argv, env));
	}
	while (swap != NULL)
	{
		ft_putstr(swap->name);
		ft_putchar('=');
		ft_putstr(swap->value);
		ft_putchar('\n');
		swap = swap->next;
	}
	return (env);
}
