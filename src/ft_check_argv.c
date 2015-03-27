/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 09:28:16 by mgras             #+#    #+#             */
/*   Updated: 2015/03/25 16:52:18 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_check_setenv(char *arg)
{
	int		ts;
	int		equal;
	int		after_equal;

	ts = 0;
	equal = 0;
	after_equal = 0;
	while (arg[ts])
	{
		if (arg[ts] == '=')
			equal = 1;
		if (arg[ts] == '=' && arg[ts + 1] != '\0')
			after_equal = 1;
		ts++;
	}
	if (equal != 1)
		ft_putstr("Setenv : No '=' in the argument\n");
	if (after_equal != 1 && equal == 1)
		ft_putstr("Setenv : No Value after Equal\n");
	if (equal == 1 && after_equal == 1)
		return (1);
	else
		return (0);
}
