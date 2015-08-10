/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/31 17:50:49 by mgras             #+#    #+#             */
/*   Updated: 2015/08/10 23:27:49 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env	*ft_free_one_env(t_env *env)
{
	t_env	*swp;

	swp = env->next;
	free(env->name);
	free(env->value);
	free(env);
	return (swp);
}

t_env	*ft_del_env(t_env *env, t_env *del)
{
	t_env	*swp;

	swp = env;
	if (del == NULL)
		return (env);
	if (del == env)
	{
		env = ft_free_one_env(env);
		return (env);
	}
	while (swp->next != del)
		swp = swp->next;
	swp->next = ft_free_one_env(del);
	return (env);
}

t_env	*ft_new_env(t_env *env, char *full)
{
	t_env	*new;
	size_t	size;

	size = 0;
	new = NULL;
	if (full == NULL)
		return (env);
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
