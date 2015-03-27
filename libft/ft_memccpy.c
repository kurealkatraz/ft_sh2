/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:35:22 by mgras             #+#    #+#             */
/*   Updated: 2015/03/06 21:52:19 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		*str1;
	const char	*str2;
	size_t		len;

	if (dst == src)
		return (dst);
	if (n == 0)
		return (NULL);
	len = 0;
	str1 = (char *)dst;
	str2 = (char *)src;
	while (len < n)
	{
		str1[len] = str2[len];
		if (str1[len] == c)
			return (str1 + len + 1);
		len++;
	}
	return (NULL);
}
