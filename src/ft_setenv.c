/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 16:45:11 by mgras             #+#    #+#             */
/*   Updated: 2015/04/29 16:45:16 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     ft_check_usenv(t_lex *med, t_env *env)
{
    t_env   *ewp;
    t_lex   *swp;

    ewp = env;
    swp = med->next;
    while (med != NULL)
    {
        if (ft_check_synt_env(med->))
    }
}

t_env   *ft_setenv(t_lex *med, t_env *env)
{
    ft_check_usenv(med, env);
    return (env);
}
