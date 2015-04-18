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
