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

void	ft_usrenv_error(char *err, int mol)
{
	ft_putstr(C_RED);
	if (mol == 000)
	{
		ft_putstr("Environement argument ");
		ft_putstr(C_CYAN);
		ft_putstr(err);
		ft_putstr(C_RED);
		ft_puendl(" is not valid, and was removed from the comand line, bitch");
	}
	else if (mol == 001)
		ft_putendl("You typing's so full of shit, I ain't going to do nothing");
	ft_putstr(C_NONE);
}

int		ft_comp_env_str(t_env *env, char *str)
{
	char	*snv;
	int		ret;

	ret = 0;
	snv = NULL;
	snv = ft_strjoin(ft_strjoin(env->name, "="), env->value);
	if (ft_strcmp(snv, str) == 0)
		ret = 1;
	if (str != NULL)
		free(str);
	return (ret);
}

void	ft_exist_env(t_env *env, t_lex *med)
{
	//get back here
}

int		ft_check_usenv(t_lex *med, t_env *env)
{
    t_env   *ewp;
    t_lex   *swp;
	t_lex	*saved;

    ewp = env;
	save = med;
    while (save != NULL)
    {
		swp = save->next;
        if (ft_lex_env(swp) == -1)
        {
            ft_usrenv_error(swp->mem, 000);
			ft_free_single_lex(save);
        }
        else
            save = save->next;
    }
	ft_exist_env(env, med)
	if (med->next == NULL)
	{
		ft_usrenv_error(NULL, 001);
		return (0);
	}
	reutrn (1);
}

t_env   *ft_setenv(t_lex *med, t_env *env)
{
    ft_check_usenv(med, env);
    return (env);
}
