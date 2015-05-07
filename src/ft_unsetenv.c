/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 16:45:23 by mgras             #+#    #+#             */
/*   Updated: 2015/04/29 16:45:25 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strcdup(char *str, char c)
{
	char	*fresh;
	size_t	len;

	len = 0;
	while (str[len] != c && str[len] != '\0')
		len++;
	fresh = ft_strndup(str, len);
	fresh[len] = '\0';
	return (fresh);
}

void	ft_usrunenv_error(char *err, int mol)
{
	ft_putstr(C_RED);
	if (mol == 000)
		ft_putendl("You typing's so full of shit, I ain't going to do nothing");
	else if (mol == 001)
	{
		ft_putstr("Environement argument ");
		ft_putstr(C_CYAN);
		ft_putstr(err);
		ft_putstr(C_RED);
		ft_putendl(" is not live.");
	}
	ft_putstr(C_NONE);
}

t_lex	*ft_check_usunenv(t_lex *med, t_env *env)
{
	t_lex	*mwp;
	t_lex	*save;


	env = env + 0;
	save = med;
	mwp = save->next;
	while (save->next != NULL)
	{
		mwp = save->next;
		if (!ft_is_env_dubs(env, mwp))
		{
			ft_usrunenv_error(mwp->mem, 001);
			save = ft_del_lex_mem(save, save->next);
		}
		else
			save = save->next;
	}
	return (med);
}

t_env	*ft_get_del_env(t_lex *med, t_env *env)
{
	t_env	*swp;

	swp = env;
	while (swp && ft_strcmp(swp->name, med->mem) != 0)
		swp = swp->next;
	return (swp);
}

t_env	*ft_unsetenv(t_lex *med, t_env *env)
{
	t_lex   *swp;

	swp = med;
	swp = ft_check_usunenv(swp, env);
	while (swp != NULL)
	{
		env = ft_del_env(env, ft_get_del_env(swp, env));
		swp = swp->next;
	}
	return (env);
}
