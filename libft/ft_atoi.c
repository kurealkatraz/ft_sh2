/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 22:15:10 by mgras             #+#    #+#             */
/*   Updated: 2015/03/06 21:48:47 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		ret;
	int		sign;
	char	*ss;

	ret = 0;
	ss = (char *)str;
	while (*ss == ' ' || *ss == '\n' || *ss == '\t' || *ss == '\r'\
	|| *ss == '\v' || *ss == '\f')
		ss++;
	sign = (*ss == '-') ? -1 : 1;
	ss = (*ss == '+' || *ss == '-') ? ss + 1 : ss;
	while (*ss >= '0' && *ss <= '9')
	{
		ret = ret * 10 + (*ss - '0');
		ss++;
	}
	ret = ret * sign;
	return (ret);
}
