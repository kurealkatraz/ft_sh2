/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 12:04:51 by mgras             #+#    #+#             */
/*   Updated: 2015/03/06 21:51:18 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*strl;
	int		ss;

	ss = 0;
	strl = ft_strdup((char const *)s);
	if (strl == NULL)
		return (NULL);
	while (strl[ss] != '\0')
	{
		strl[ss] = f(ss, strl[ss]);
		ss++;
	}
	return (strl);
}
