/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/17 17:19:23 by mgras             #+#    #+#             */
/*   Updated: 2015/04/17 17:35:57 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		{
			swipe++;
			while (dirty_pleb[swipe] != '"' && dirty_pleb[swipe])
			{
				swipe++;
				len++;
			}
		}
		else if (dirty_pleb[swipe == '\''])
		{
			swipe++;
			while (dirty_pleb[swipe] != '\'' && dirty_pleb[swipe])
			{
				swipe++;
				len++;
			}
		}
		else if (dirty_pleb[swipe] == ' ' || dirty_pleb[swipe] == '\t')
		{
			while ((dirty_pleb[swipe] == ' ' || dirty_pleb[swipe]
						== '\t') && dirty_pleb[swipe] != '\0')
				swipe++;
			if (dirty_pleb[swipe != '\0'])
				len++;
		}
		else
		{
			swipe++;
			len++;
		}
	}
	return (len);
}

char	*ft_clean_str(char *dirty_pleb)
{
	char	*clean_pleb;
	int		ts;
	int		ss;

	ts = 0;
	ss = 0;
	while (dirty_pleb[ts] == ' ' || dirty_pleb[ts] == '\t')
		ts++;
	clean_pleb = (char*)malloc(sizeof(char) * (ft_clean_len(dirty_pleb)));
	ft_bzero(clean_pleb, ft_clean_len(dirty_pleb) + 1);
	while (dirty_pleb[ts] != '\0')
	{
		if (dirty_pleb[ts] == '"')
		{
			clean_pleb[ss++] = dirty_pleb[ts++];
			while (dirty_pleb[ts] != '"' && dirty_pleb[ts] != '\0')
				clean_pleb[ss++] = dirty_pleb[ts++];
			clean_pleb[ss++] = dirty_pleb[ts++];
		}
		else if (dirty_pleb[ts] == '\'')
		{
			clean_pleb[ss++] = dirty_pleb[ts++];
			while (dirty_pleb[ts] != '\'' && dirty_pleb[ts] != '\0')
				clean_pleb[ss++] = dirty_pleb[ts++];
			clean_pleb[ss++] = dirty_pleb[ts++];
		}
		else if (dirty_pleb[ts] == ' ' || dirty_pleb[ts] == '\t')
		{
			while ((dirty_pleb[ts] == ' ' || dirty_pleb[ts] ==
						'\t') && dirty_pleb[ts] != '\0')
				ts++;
			if (dirty_pleb[ts] != '\0' && ss != 0)
				clean_pleb[ss++] = ' ';
		}
		else
			clean_pleb[ss++] = dirty_pleb[ts++];
	}
	clean_pleb[ss++] = '\0';
	free(dirty_pleb);
	return (clean_pleb);
}
