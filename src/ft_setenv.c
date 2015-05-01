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
	t_env	*swp;
	char	*snv;
	int		ret;

	ret = 0;
	swp = env;
	snv = NULL;
	snv = ft_strjoin(ft_strjoin(swp->name, "="), swp->value);
	if (ft_strcmp(snv, str) == 0)
		ret = 1;
	free(snv);
	return (ret);
}

t_lex	*ft_exist_env(t_env *env, t_lex *med)
{
	t_env	*swipe;
	t_lex	*medivac;
	t_lex	*save;

	save = med;
	medivac = save->next;
	while (medivac != NULL && save != NULL)
	{
		medivac = save->next;
		swipe = env;
		while (swipe != NULL && medivac != NULL)
		{
			if (!ft_comp_env_str(swipe, medivac->mem))
			{
				ft_usrenv_error(medivac->mem, 002);
				ft_free_single_lex(save);
				swipe = NULL;
			}
			if (swipe)
				swipe = swipe->next;
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
		ft_usrenv_error(NULL, 001);
	return (med->next);
}

void	ft_put_at_end_env(t_env *env, char *full)
{
	t_env	*new;
	t_env	*swp;
	size_t	size;

	size = 0;
	swp = env;
	new = NULL;
	if (full == NULL || env == NULL)
		return ;
	while (full[size] != '\0' && full[size] != '=')
		size++;
	new = (t_env*)malloc(sizeof(t_env));
	new->next = NULL;
	new->name = (char*)malloc(sizeof(char) * (size + 1));
	new->name = ft_strncpy(new->name, full, size);
	new->value = ft_strsub(full, size + 1, (ft_strlen(full) - size));
	while (swp->next != NULL)
		swp = swp->next;
	swp->next = new;
}

t_env   *ft_setenv(t_lex *med, t_env *env)
{
	t_lex	*swp;

	swp = med;
	swp = ft_check_usenv(med, env);
	while(swp != NULL)
	{
		ft_put_at_end_env(env, swp->mem);
		swp = swp->next;
	}
    return (env);
}
