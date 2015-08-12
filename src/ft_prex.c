/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/07 18:49:25 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 12:16:37 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env	*ft_muzukashi(t_lex *med, t_env *env)
{
	if (!ft_ispath(med->mem) && med->path == NULL && !ft_is_buildtin(med->mem))
		ft_scann_eror(005, med->mem);
	else
		env = ft_parser(med, env);
	return (env);
}
