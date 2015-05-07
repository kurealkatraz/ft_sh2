/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 16:04:36 by mgras             #+#    #+#             */
/*   Updated: 2015/04/12 17:26:51 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_is_env_dubs(t_env *env, t_lex *med)
{
	t_env	*ewp;
	char	*str;
	int		len;

	ewp = env;
	len = 0;
	if (!med)
		return (0);
	while (med->mem[len] != '=' && med->mem[len])
		len++;
	str = ft_strndup(med->mem, len);
	while (ewp != NULL)
	{
		if (ft_strcmp(str, ewp->name) == 0)
		{
			ft_strdel(&str);
			return (1);
		}
		ewp = ewp->next;
	}
	ft_strdel(&str);
	return (0);
}

int		ft_is_dubs(t_lex *med)
{
	t_lex	*swp;
	int		e_size;

	e_size = 0;
	while (med->mem[e_size] != '=')
		e_size++;
	swp = med->next;
	while (swp != NULL)
	{
		if (ft_strncmp(swp->mem, med->mem, e_size) == 0)
			return (1);
		swp = swp->next;
	}
	return (0);
}

int		ft_is_buildtin(char *str)
{
	if (ft_strcmp(str, "env") == 0)
		return (1);
	else if(ft_strcmp(str, "setenv") == 0)
		return (1);
	else if(ft_strcmp(str, "unsetenv") == 0)
		return (1);
	else if(ft_strcmp(str, "cd") == 0)
		return (1);
	return (0);
}

int		ft_isenvmem(char *str)
{
	int		pos;

	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '=')
		return (1);
		pos ++;
	}
	return (0);
}

int		ft_ispath(char *str)
{
	int		ts;

	ts = 0;
	while (str[ts])
		if (str[ts++] == '/')
			return (1);
	return (0);
}

int		ft_isredi(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int		ft_isalien(char c)
{
	if (c == '"' || c == '\'' || c == ' ' || c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int		ft_iscompl(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}
