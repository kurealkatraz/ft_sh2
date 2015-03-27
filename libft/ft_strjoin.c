/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 16:25:03 by mgras             #+#    #+#             */
/*   Updated: 2015/03/22 15:23:33 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*fresh;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	len = 1 + ft_strlen(s1) + ft_strlen(s2);
	if (!(fresh = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	fresh = ft_strcpy(fresh, s1);
	fresh = ft_strcat(fresh, s2);
	return (fresh);
}
