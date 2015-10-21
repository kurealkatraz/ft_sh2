/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 23:17:14 by mgras             #+#    #+#             */
/*   Updated: 2015/10/21 12:59:45 by mgras            ###   ########.fr       */
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
	int		inbraces;
	int		inminbra;
	int		get_out;

	get_out = 0;
	inbraces = -1;
	inminbra = -1;
	while (line[*ss] && !get_out)
	{
		if (line[*ss] == ';' && inbraces == -1 && inminbra == -1)
			get_out = 1;
		else if (line[*ss] == '\"' && inminbra == -1)
			inbraces = -inbraces;
		else if (line[*ss] == '\'' && inbraces == -1)
			inminbra = -inminbra;
		*ss = *ss + 1;
	}
	len = ft_get_proper_len(line, ts, *ss);
	return (ft_strsub(line, ts, len));
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
	free(ext);
}
