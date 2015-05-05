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
	if (str[len] == '\0')
	{
		free(fresh);
		return (NULL);
	}
	return (fresh);
}

t_lex	*ft_check_usunenv(t_lex *med, t_env *env)
{
	t_lex	*mwp;
	//char	*str;

	mwp = med->next;
	env = env + 0;
	while (mwp != NULL)
	{
		mwp = mwp->next;
	}
	return (mwp);
}

t_env	*ft_unsetenv(t_env *env, t_lex *med)
{
	t_lex   *swp;

	swp = med;
	swp = ft_check_usunenv(swp, env);
	while (swp != NULL)
	{
		//env = ft_del_shit(swp, env);
		swp = swp->next;
	}
	return (env);
}
