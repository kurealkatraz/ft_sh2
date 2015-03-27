/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 23:19:01 by mgras             #+#    #+#             */
/*   Updated: 2015/03/22 15:19:20 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (size > 1)
	{
		mem = (void*)malloc(size);
		if (mem == NULL)
			return (NULL);
		while (size--)
			ft_bzero(mem, size);
	}
	else
		mem = NULL;
	return (mem);
}
