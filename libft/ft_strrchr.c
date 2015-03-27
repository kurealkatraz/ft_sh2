/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 21:43:56 by mgras             #+#    #+#             */
/*   Updated: 2015/03/06 21:51:43 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*newsr;

	newsr = (char *)s + ft_strlen(s);
	while (*newsr != c)
	{
		if (newsr == s)
			return (NULL);
		newsr--;
	}
	return (newsr);
}
