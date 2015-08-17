/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex_mcr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 15:36:14 by mgras             #+#    #+#             */
/*   Updated: 2015/04/04 15:36:46 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lex	*ft_free_lex(t_lex *medivac)
{
	t_lex	*swp;

	swp = medivac;
	while (swp != NULL)
	{
		ft_strdel(&swp->mem);
		if (swp->path)
			ft_strdel(&swp->path);
		medivac = medivac->next;
		free(swp);
		swp = medivac;
	}
	return (swp);
}

t_lex	*ft_new_meme(t_lex *med, char *meme)
{
	t_lex	*new;

	if (!(new = (t_lex*)malloc(sizeof(t_lex))))
		return (med);
	if (!(new->mem = (char*)malloc(sizeof(char) * (ft_strlen(meme) + 1))))
	{
		free(new);
		return (med);
	}
	ft_strcpy(new->mem, meme);
	new->next = med;
	return (new);
}

t_lex	*ft_rev_lex(t_lex *medivac)
{
	t_lex	*reved;
	t_lex	*swp;

	swp = medivac;
	reved = NULL;
	while (swp != NULL)
	{
		reved = ft_new_meme(reved, swp->mem);
		if (swp->path)
			reved->path = ft_strdup(swp->path);
		else
			reved->path = NULL;
		swp = swp->next;
	}
	ft_free_lex(medivac);
	return (reved);
}
