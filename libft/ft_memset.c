/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:04:45 by mgras             #+#    #+#             */
/*   Updated: 2015/03/06 21:49:29 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*curr;

	if (len <= 0)
		return (b);
	curr = (unsigned char *)b;
	while (len--)
		*curr++ = (unsigned char)c;
	return (b);
}
