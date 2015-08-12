/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 16:04:36 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 11:32:44 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_is_what_len_pipe(t_lex *med)
{
	t_lex	*swp;
	int		len;

	len = 0;
	swp = med;
	while (swp && !ft_ispipe(swp->mem[0]))
	{
		swp = swp->next;
		len++;
	}
	return (len);
}

int		ft_is_next_op_pipe(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (swp != NULL)
	{
		if (ft_ispipe(swp->mem[0]))
			return (1);
		swp = swp->next;
	}
	return (0);
}
