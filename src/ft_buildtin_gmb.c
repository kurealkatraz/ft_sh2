/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildtin_gmb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/14 10:27:47 by mgras             #+#    #+#             */
/*   Updated: 2015/03/25 16:53:01 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_cd_errors(int index, char *erred)
{
	if (index == 0)
	{
		ft_putstr(erred);
		ft_putstr(" : Is not a Valid name for a Directory\n");
	}
	else if (index == 1)
		ft_putstr("U WOT M8 ? REMOVING HOME JUST LIKE THAT ? OH HELL NO\n");
	else if (index == 2)
		ft_putstr("Nope dis ain't goin to work mate\n");
}

t_env	*ft_home_cd(t_env *env)
{
	t_env	*swp;

	swp = env;
	env = ft_maj_old(env);
	while (swp != NULL)
	{
		if (ft_strcmp(swp->name, "HOME") == 0)
			return (ft_cd(env, swp->value));
		swp = swp->next;
	}
	ft_cd_errors(1, NULL);
	return (env);
}

t_env	*ft_maj_pwd(t_env *env)
{
	t_env	*swap;
	char	*buff;

	swap = env;
	while (swap != NULL && 0 != ft_strcmp(swap->name, "PWD"))
		swap = swap->next;
	buff = (char*)malloc(sizeof(char) * (PATH_MAX + 5));
	if (swap == NULL)
	{
		buff = ft_strcpy(buff, "PWD=");
		buff = ft_strcat (buff, getcwd(NULL, PATH_MAX));
		env = ft_setenv(env, buff);
		return (env);
	}
	free(swap->value);
	buff = getcwd(buff, PATH_MAX);
	swap->value = (char*)malloc(sizeof(char) * (ft_strlen(buff) + 1));
	swap->value = ft_strcpy(swap->value, buff);
	free(buff);
	return (env);
}

t_env	*ft_maj_old(t_env *env)
{
	t_env	*swp;
	t_env	*pwd;

	swp = env;
	pwd = env;
	while (ft_strcmp(swp->name, "OLDPWD") != 0 && swp->next != NULL)
		swp = swp->next;
	while (ft_strcmp(pwd->name, "PWD") != 0 && pwd->next)
		pwd = pwd->next;
	if (ft_strcmp(swp->name, "OLDPWD") != 0)
		ft_setenv(env, ft_strjoin("OLDPWD=./", pwd->value));
	else
	{
		env = ft_unsetenv(env, "OLDPWD");
		env = ft_setenv(env, ft_strjoin("OLDPWD=", pwd->value));
	}
	return (env);
}
