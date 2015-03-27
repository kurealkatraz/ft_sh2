/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vorpalblade_snickersnack.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 18:36:49 by mgras             #+#    #+#             */
/*   Updated: 2015/03/25 17:15:01 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_bentobox_sushisnatch(char **argv, char *cmp, int pos)
{
	int		cmplen;

	cmplen = 0;
	while (cmp[cmplen] != '=')
		cmplen++;
	while (argv[pos] != NULL)
	{
		if (ft_strncmp(cmp, argv[pos++], cmplen) == 0)
			return (1);
	}
	return (0);
}

void	ft_bellatrix_cuddlecunt(char **argv)
{
	int		pos;

	pos = 2;
	while (argv[pos] != NULL)
	{
		if (ft_bentobox_sushisnatch(argv, argv[pos], pos + 1) == 0)
			ft_putendl(argv[pos]);
		pos++;
	}
}
