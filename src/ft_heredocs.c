/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/04 18:23:09 by mgras             #+#    #+#             */
/*   Updated: 2015/08/05 09:22:00 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_left_d_redi(t_lex *med, t_lex *curr, t_env *env)
{
  char  **argv;
  char  **envp;
  char  *bin;
  
  if (med == curr)
    ft_solo_heredocs(curr, env);

}
