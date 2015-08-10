/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexeur_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 23:31:18 by mgras             #+#    #+#             */
/*   Updated: 2015/08/10 23:32:32 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lex	*ft_alpha_lex(int *s, char *line, t_lex *med)
{
	t_lex	*new_lex;
	int		ss;

	ss = 0;
	new_lex = NULL;
	if (!(new_lex = (t_lex*)malloc(sizeof(t_lex))))
		return (med);
	while (ft_isalien(line[ss]) == 0 && line[ss] != 0)
	{
		ss++;
		(*s) = (*s) + 1;
	}
	if (!(new_lex->mem = (char*)malloc(sizeof(char) * (ss + 1))))
	{
		free(new_lex);
		return (med);
	}
	ft_strncpy(new_lex->mem, line, ss);
	new_lex->next = med;
	if (!new_lex)
		return (med);
	return (new_lex);
}
