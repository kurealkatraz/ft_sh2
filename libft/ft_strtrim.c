/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 16:41:20 by mgras             #+#    #+#             */
/*   Updated: 2015/03/06 21:54:08 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		len;
	int		start;
	int		end;

	len = 0;
	start = 0;
	end = ft_strlen(s);
	while ((s[start] == ' ' || s[start] == '\t'
		|| s[start] == '\n') && s[start])
		start++;
	if (start < end)
		end--;
	while ((s[end] == ' ' || s[end] == '\t' || s[end] == '\n') && end > start)
		end--;
	len = end - start;
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	len = 0;
	while (start <= end)
		str[len++] = s[start++];
	str[len] = '\0';
	return (str);
}
