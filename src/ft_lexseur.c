/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexseur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/31 15:42:23 by mgras             #+#    #+#             */
/*   Updated: 2015/08/10 18:12:00 by mgras            ###   ########.fr       */
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

t_lex	*ft_compl_lex(int *s, char *line, t_lex *med)
{
	t_lex	*next_lex;
	int		ss;

	next_lex = NULL;
	if (line[1] == line[0] && line[0] != '|')
		ss = 2;
	else
		ss = 1;
	if (!(next_lex = (t_lex*)malloc(sizeof(t_lex))))
		return (med);
	if (!(next_lex->mem = (char*)malloc(sizeof(char) * (ss + 1))))
	{
		free(next_lex);
		return (med);
	}
	ft_strncpy(next_lex->mem, line, ss);
	next_lex->next = med;
	*s += ss;
	if (!next_lex)
		return (med);
	return (next_lex);
}

t_lex	*ft_singlebrace(t_lex *med, char q)
{
	t_lex	*new_brace;

	if (!(new_brace = (t_lex*)malloc(sizeof(t_lex))))
		return (med);
	if (!(new_brace->mem = (char*)malloc(sizeof(char) * 2)))
		return (med);
	new_brace->mem[0] = q;
	new_brace->mem[1] = '\0';
	new_brace->next = med;
	return (new_brace);
}

t_lex	*ft_braced_lex(int *s, char *line, t_lex *med, char q)
{
	t_lex	*new_lex;
	int		ss;

	ss = 0;
	(*s) = (*s) + 1;
	new_lex = NULL;
	if (line[ss + 1] == '\0')
		return (ft_singlebrace(med, q));
	if (!(new_lex = (t_lex*)malloc(sizeof(t_lex))))
		return (med);
	while (line[++ss] != q && line[ss])
		(*s) = (*s) + 1;
	(*s) = (*s) + 1;
	if (!(new_lex->mem = (char*)malloc(sizeof(char) * (ss + 1))))
		return (med);
	ft_strncpy(new_lex->mem, line, ss + 1);
	new_lex->next = med;
	if (!new_lex)
		return (med);
	return (new_lex);
}

t_lex	*ft_next_lex(t_lex *med, int *s, char *line)
{
	if (!ft_isalien(line[0]))
		return (ft_alpha_lex(s, line, med));
	else if (line[0] == '>' || line[0] == '<' || line[0] == '|')
		return (ft_compl_lex(s, line, med));
	else if ((line[0] == '\"' || line[0] == '\''))
		return (ft_braced_lex(s, line, med, line[0]));
	else
	{
		(*s) = (*s) + 1;
		return (med);
	}
}

t_lex	*ft_lexor(char *line)
{
	t_lex	*med;
	int		*markpos;

	markpos = (int*)malloc(sizeof(int) * 1);
	med = NULL;
	*markpos = 0;
	if (line == NULL)
		return (med);
	while (line[*markpos])
		med = ft_next_lex(med, markpos, line + (*markpos));
	free(markpos);
	return (med);
}
