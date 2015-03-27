/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 15:24:00 by mgras             #+#    #+#             */
/*   Updated: 2015/03/25 17:11:21 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	e_no_match_env(char *erred_str)
{
	ft_putstr("unsetenv : No match foud for ");
	ft_putstr(erred_str);
	ft_putchar('\n');
}

void	e_no_such_path(char *erred_str)
{
	ft_putstr("cd : No such directory \"");
	ft_putstr(erred_str);
	ft_putstr("\"\n");
}
