/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/31 17:44:58 by mgras             #+#    #+#             */
/*   Updated: 2015/08/09 10:29:34 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_get_proper_len(char *line, int ts, int ss)
{
	int		len;

	len = 0;
	while (line[ts] && line[ts] != ';' && ts <= ss)
	{
		ts++;
		len++;
	}
	return (len);
}

char	*ft_split_line(char *line, int *ss, int len, int ts)
{
	int		inBraces;
	int		inminBra;
	int		get_out;

	get_out = 0;
	inBraces = -1;
	inminBra = -1;
	while (line[*ss] && !get_out)
	{
		if (line[*ss] == ';' && inBraces == -1 && inminBra == -1)
			get_out = 1;
		else if (line[*ss] == '\"')
			inBraces = -inBraces;
		else if (line[*ss] == '\'')
			inminBra = -inminBra;
		*ss = *ss + 1;
	}
	len = ft_get_proper_len(line , ts, *ss);
	return (ft_clean_str(ft_strsub(line, ts, len)));
}

t_env	*ft_core(char *line, t_env *env, int *ext)
{
	char	*send;
	int		*ss;

	line = ft_clean_str(line);
	ss = (int*)malloc(sizeof(int) * 1);
	*ss = 0;
	while (line[*ss])
	{
		send = ft_split_line(line, ss, 0, *ss);
		env = ft_child_molesting(send, env, ext);
		ft_strdel(&send);
	}
	free(line);
	free(ss);
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
