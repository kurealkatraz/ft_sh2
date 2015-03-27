/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:44:19 by mgras             #+#    #+#             */
/*   Updated: 2015/03/06 21:49:26 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dstp;
	const unsigned char	*srcp;

	dstp = (unsigned char *)dst;
	srcp = (const unsigned char *)src;
	if (dstp < srcp)
		while (len-- != 0)
			*dstp++ = *srcp++;
	else
	{
		dstp += len;
		srcp += len;
		while (len-- > 0)
			*--dstp = *--srcp;
	}
	return (dst);
}
