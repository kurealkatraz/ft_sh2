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

t_env	*ft_core(char *line, t_env *env)
{
	int		out;

	out = 0;
	line = ft_clean_str(line);
	out = ft_child_molesting(line, env);
	free(line);
	if (out == 1)
	{
		//ft_free_all_env
		return (NULL);
	}
	return (env);
}

void	ft_prompt(char **envp, t_env *env)
{
	char	*line;

	while (env != NULL)
	{
		line = NULL;
		ft_colors(envp);
		if (1 == ft_get_next_line(0, &line))
		{
			if (line[0] != '\0')
				env = ft_core(line, env);
		}
		else
			exit(-1);
	}
	//env = ft_free_all_env(env);
	(void)envp;
}

t_env	*shlvl_pp(t_env *env)
{
	t_env	*swap;
	int		inception;

	swap = env;
	while (swap->next != NULL && 0 != ft_strncmp("SHLVL", swap->name, 5))
		swap = swap->next;
	if (swap->next == NULL)
		return (swap);
	inception = ft_atoi(swap->value) + 1;
	free(swap->value);
	swap->value = ft_itoa(inception);
	return (env);
}

int		main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = ft_get_env(NULL, envp);
	env = shlvl_pp(env);
	ft_prompt(envp, env);
	argv = argv + 0;
	argc = argc + 0;
	return (0);
}