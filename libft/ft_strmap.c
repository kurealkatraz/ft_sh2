/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 12:00:18 by mgras             #+#    #+#             */
/*   Updated: 2015/03/06 21:33:08 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*strl;
	int		ss;

	ss = 0;
	strl = ft_strdup((char const *)s);
	if (strl == NULL)
		return (NULL);
	while (strl[ss] != '\0')
	{
		strl[ss] = f(strl[ss]);
		ss++;
	}
	return (strl);
}
