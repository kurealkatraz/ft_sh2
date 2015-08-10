/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaner_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 23:15:20 by mgras             #+#    #+#             */
/*   Updated: 2015/08/10 23:16:39 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_clean_split1(char *dirty_pleb, int *swipe, int *len)
{
	*swipe = *swipe + 1;
	while (dirty_pleb[*swipe] != '"' && dirty_pleb[*swipe])
	{
		*swipe = *swipe + 1;
		*len = *len + 1;
	}
}

void	ft_clean_split2(char *dirty_pleb, int *swipe, int *len)
{
	*swipe = *swipe + 1;
	while (dirty_pleb[*swipe] != '\'' && dirty_pleb[*swipe])
	{
		*swipe = *swipe + 1;
		*len = *len + 1;
	}
}

void	ft_clean_split3(char *dirty_pleb, int *swipe, int *len)
{
	while ((dirty_pleb[*swipe] == ' ' || dirty_pleb[*swipe]
	== '\t') && dirty_pleb[*swipe] != '\0')
		*swipe = *swipe + 1;
	if (dirty_pleb[*swipe != '\0'])
		*len = *len + 1;
}

int		ft_clean_len(char *dirty_pleb)
{
	int		len;
	int		swipe;

	swipe = 0;
	len = 0;
	while (*dirty_pleb == ' ' || *dirty_pleb == '\t')
		dirty_pleb++;
	while (dirty_pleb[swipe])
	{
		if (dirty_pleb[swipe] == '"')
			ft_clean_split1(dirty_pleb, &swipe, &len);
		else if (dirty_pleb[swipe == '\''])
			ft_clean_split2(dirty_pleb, &swipe, &len);
		else if (dirty_pleb[swipe] == ' ' || dirty_pleb[swipe] == '\t')
			ft_clean_split3(dirty_pleb, &swipe, &len);
		else
		{
			swipe++;
			len++;
		}
	}
	return (len);
}
