/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correction_center.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 18:26:15 by mgras             #+#    #+#             */
/*   Updated: 2015/04/05 14:20:27 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lex	*ft_comp_scan(t_lex *med)
{
	if (med->next == NULL)
	{
		ft_scann_eror(002, med->mem);
		return (NULL);
	}
	else if (ft_iscompl(med->next->mem[0]))
	{
		ft_scann_eror(003, med->mem);
		return (NULL);
	}
	return (med);
}

t_lex	*ft_braced_scan(t_lex *med, char brace)
{
	int		ts;

	ts = 1;
	if (med->mem[ts] == '\0')
	{
		ft_scann_eror(001, med->mem);
		return (NULL);
	}
	while (med->mem[ts])
		ts++;
	if (med->mem[ts - 1] != brace)
	{
		ft_scann_eror(001, med->mem);
		return (NULL);
	}
	return (med);
}

t_lex	*ft_scaner(t_lex *med)
{
	if (med->mem[0] == '>' || med->mem[0] == '<' || med->mem[0] == '|')
		return (ft_comp_scan(med));
	else if ((med->mem[0] == '"' || med->mem[0] == '\''))
		return (ft_braced_scan(med, med->mem[0]));
	else
		return (med);
}

t_lex	*ft_correction_facility(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (swp != NULL)
	{
		if (ft_is_buildtin(swp->mem))
		{
			while (!ft_iscompl(swp->mem[0]))
			{
				if (swp->next == NULL)
					return (med);
				swp = swp->next;
			}
		}
		else if (!(swp = ft_scaner(swp)))
		{
			med = ft_free_lex(med);
			return (NULL);
		}
		swp = swp->next;
	}
	return (med);
}
