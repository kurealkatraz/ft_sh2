/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 15:46:17 by mgras             #+#    #+#             */
/*   Updated: 2015/03/25 17:10:21 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_env	*ft_core(char *line, t_env *env)
{
	char	**argv;
	char	*path;

	line = ft_clean_str(line);
	argv = ft_strsplit(line, ' ');
	if (1 == ft_is_builtin(argv[0]))
		env = ft_builtin(argv, env);
	else
	{
		if ((path = ft_find_bin(argv[0], env)) == NULL)
			ft_putstr("Command not found\n");
		else
			ft_new_process(path, argv, env);
	}
	free(line);
	ft_free_argv(argv);
	return (env);
}

void	ft_prompt(char **envp, t_env *env)
{
	char	*line;

	while (42)
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
	env = ft_free_all_env(env);
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
	argv = argv + 1;
	argc = argc + 1;
	return (0);
}
