/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 19:29:02 by mgras             #+#    #+#             */
/*   Updated: 2015/03/22 15:27:01 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new;

	if (!(new = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	new = ft_strcpy(new, s1);
	return (new);
}
