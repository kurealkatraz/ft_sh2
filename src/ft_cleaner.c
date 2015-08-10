/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/17 17:19:23 by mgras             #+#    #+#             */
/*   Updated: 2015/08/10 20:37:23 by mgras            ###   ########.fr       */
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

char	*ft_cstr_split1(char *clean_pleb, char *dirty_pleb, int *ts, int *ss)
{
	clean_pleb[*ss] = dirty_pleb[*ts];
	*ss = *ss + 1;
	*ts = *ts + 1;
	while (dirty_pleb[*ts] != '"' && dirty_pleb[*ts] != '\0')
	{
		clean_pleb[*ss] = dirty_pleb[*ts];
		*ss = *ss + 1;
		*ts = *ts + 1;
	}
	clean_pleb[*ss] = dirty_pleb[*ts];
	*ss = *ss + 1;
	*ts = *ts + 1;
	return (clean_pleb);
}

char	*ft_cstr_split2(char *clean_pleb, char *dirty_pleb, int *ts, int *ss)
{
	clean_pleb[*ss] = dirty_pleb[*ts];
	*ss = *ss + 1;
	*ts = *ts + 1;
	while (dirty_pleb[*ts] != '\'' && dirty_pleb[*ts] != '\0')
	{
		clean_pleb[*ss] = dirty_pleb[*ts];
		*ss = *ss + 1;
		*ts = *ts + 1;
	}
	clean_pleb[*ss] = dirty_pleb[*ts];
	*ss = *ss + 1;
	*ts = *ts + 1;
	return (clean_pleb);
}

char	*ft_cstr_split3(char *clean_pleb, char *dirty_pleb, int *ts, int *ss)
{
	while ((dirty_pleb[*ts] == ' ' || dirty_pleb[*ts] ==
	'\t') && dirty_pleb[*ts] != '\0')
		*ts = *ts + 1;
	if (dirty_pleb[*ts] != '\0' && *ss != 0)
	{
		clean_pleb[*ss] = ' ';
		*ss = *ss + 1;
	}
	return (clean_pleb);
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
			clean_pleb = ft_cstr_split1(clean_pleb, dirty_pleb, &ts, &ss);
		else if (dirty_pleb[ts] == '\'')
			clean_pleb = ft_cstr_split2(clean_pleb, dirty_pleb, &ts, &ss);
		else if (dirty_pleb[ts] == ' ' || dirty_pleb[ts] == '\t')
			clean_pleb = ft_cstr_split3(clean_pleb, dirty_pleb, &ts, &ss);
		else
			clean_pleb[ss++] = dirty_pleb[ts++];
	}
	clean_pleb[ss++] = '\0';
	free(dirty_pleb);
	return (clean_pleb);
}
