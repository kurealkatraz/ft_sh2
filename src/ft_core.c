/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/31 17:44:58 by mgras             #+#    #+#             */
/*   Updated: 2015/04/17 17:46:35 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env	*ft_core(char *line, t_env *env, int *ext)
{
	line = ft_clean_str(line);
	env = ft_child_molesting(line, env, ext);
	free(line);
	return (env);
}

void	ft_prompt(char **envp, t_env *env)
{
	char	*line;
	int		*ext;

	ext = (int*)malloc(sizeof(int));
	*ext = 0;
	while (*ext == 0)
	{
		line = NULL;
		ft_colors(envp);
		if (1 == ft_get_next_line(0, &line))
		{
			if (line[0] != '\0')
				env = ft_core(line, env, ext);
		}
	}
}

t_env	*shlvl_pp(t_env *env)
{
	t_env	*swap;
	int		inception;

	swap = env;
	while (swap->next != NULL && 0 != ft_strncmp("SHLVL", swap->name, 5))
		swap = swap->next;
	if (swap->next == NULL)
		return (env);
	inception = ft_atoi(swap->value) + 1;
	free(swap->value);
	swap->value = ft_itoa(inception);
	return (env);
}

t_env	*ft_get_min_env(t_env *env)
{
	env = ft_new_env(env, "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	return (env);
}

int		main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = NULL;
	if (*envp != NULL)
		env = ft_get_env(env, envp);
	if (ft_get_del_env("PATH", env) == NULL)
		env = ft_get_min_env(env);
	env = shlvl_pp(env);
	ft_prompt(envp, env);
	argv = argv + 0;
	argc = argc + 0;
	return (0);
}
