/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 19:58:04 by mgras             #+#    #+#             */
/*   Updated: 2015/03/06 21:53:12 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*str;
	char	*swipe;
	size_t	len;

	str = (char *)ft_memchr(dst, '\0', size);
	if (str == NULL)
		return (size + ft_strlen(src));
	swipe = (char *)src;
	len = (size_t)(str - dst) + ft_strlen(swipe);
	while ((size_t)(str - dst) < size - 1 && *swipe != '\0')
	{
		*str = *swipe;
		str++;
		swipe++;
	}
	*str = '\0';
	return (len);
}
