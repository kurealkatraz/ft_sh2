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
		ft_putendl(" is not valid, and was removed from the comand line, bitch");
	}
	else if (mol == 001)
		ft_putendl("You typing's so full of shit, I ain't going to do nothing");
	if (mol == 002)
	{
		ft_putstr("Environement argument ");
		ft_putstr(C_CYAN);
		ft_putstr(err);
		ft_putstr(C_RED);
		ft_putendl(" is already live. So I corrected the command line fam");
	}
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

t_lex	*ft_exist_env(t_env *env, t_lex *med)
{
	t_env	*swipe;
	t_lex	*medivac;
	t_lex	*save;

	save = med;
	while (medivac != NULL)
	{
		medivac = save->next;
		swipe = env;
		while (swipe != NULL && medivac != NULL)
		{
			if (!ft_comp_env_str(swipe, medivac->mem))
			{
				ft_usrenv_error(medivac->mem, 002);
				ft_free_single_lex(save);
			}
		}
		save = save->next;
	}
	return (med);
}

t_lex	*ft_check_usenv(t_lex *med, t_env *env)
{
    t_lex   *swp;
	t_lex	*save;

	save = med;
    while (save != NULL)
    {
		swp = save->next;
    	if (ft_lex_env(swp) == -1)
    	{
        	ft_usrenv_error(swp->mem, 000);
			save = ft_free_single_lex(save);
    	}
        else
            save = save->next;
    }
	med = ft_exist_env(env, med);
	if (med->next == NULL)
	{
		ft_usrenv_error(NULL, 001);
		return (NULL);
	}
	return (med);
}

t_env   *ft_setenv(t_lex *med, t_env *env)
{
	t_lex	*swp;

	swp = med;
	swp = ft_check_usenv(med, env);
	while(swp != NULL)
	{
		env = ft_new_env(env, swp->mem);
		swp = swp->next;
	}
    return (env);
}
