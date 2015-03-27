/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 15:46:15 by mgras             #+#    #+#             */
/*   Updated: 2015/03/25 17:04:16 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**ft_get_envp(t_env *env)
{
	char	**envp;
	t_env	*swap;
	int		i;
	int		len;

	swap = env;
	i = 0;
	while ((swap = swap->next) != NULL)
		i++;
	envp = (char**)malloc(sizeof(char*) * (i + 1));
	envp[i + 1] = NULL;
	swap = env;
	i = 0;
	while (swap != NULL)
	{
		len = ft_strlen(swap->value) + ft_strlen(swap->name) + 2;
		envp[i] = (char*)malloc(sizeof(char) * len);
		envp[i] = ft_strcpy(envp[i], swap->name);
		envp[i] = ft_strcat(envp[i], "=");
		envp[i] = ft_strcat(envp[i], swap->value);
		i++;
		envp[i] = NULL;
		swap = swap->next;
	}
	return (envp);
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
