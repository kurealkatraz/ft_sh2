/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhat_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/12 11:32:55 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 11:33:09 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

int		ft_is_what_len(t_lex *med)
{
	t_lex	*swp;
	int		len;

	len = 0;
	swp = med;
	while (swp)
	{
		swp = swp->next;
		len++;
	}
	return (len);
}
