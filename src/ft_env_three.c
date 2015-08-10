/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 23:26:42 by mgras             #+#    #+#             */
/*   Updated: 2015/08/10 23:27:43 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_env_noexec(t_lex *med)
{
	t_lex	*mwp;

	mwp = med;
	while (mwp != NULL && !ft_iscompl(mwp->mem[0]))
	{
		if ((ft_ispath(mwp->mem) || mwp->path) && !ft_is_buildtin(mwp->mem))
			return (0);
		mwp = mwp->next;
	}
	return (1);
}

t_lex	*ft_del_lex_mem(t_lex *prev, t_lex *curr)
{
	if (prev == curr)
	{
		free(prev->mem);
		curr = prev->next;
		free(prev);
		return (curr);
	}
	prev->next = curr->next;
	free(curr->mem);
	free(curr);
	return (prev);
}
