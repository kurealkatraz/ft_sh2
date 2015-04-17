/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chldabs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/31 18:05:14 by mgras             #+#    #+#             */
/*   Updated: 2015/04/17 18:23:30 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lex	*ft_get_bin(t_lex *med, t_pth *pth)
{
	DIR				*cont;
	struct dirent	*in;
	t_pth			*pwp;

	pwp = pth;
	while (pwp != NULL)
	{
		cont = opendir(pwp->path);
		if (cont != NULL)
		{
			while ((in = readdir(cont)) != NULL)
			{
				if (!ft_strcmp(in->d_name, med->mem))
				{
					closedir(cont);
					med->path = ft_strdup(pwp->path);
					return (med);
				}
			}
			closedir(cont);
		}
		pwp = pwp->next;
	}
	med->path = NULL;
	return (med);
}

t_lex	*ft_asign_path(t_pth *pth, t_lex *med)
{
	t_pth	*pwp;
	t_lex	*mwp;

	pwp = pth;
	mwp = med;
	while (mwp != NULL)
	{
		if (!ft_ispath(mwp->mem) && !(ft_isalien(mwp->mem[0])))
			mwp = ft_get_bin(mwp, pth);
		else
			mwp->path = NULL;
		mwp = mwp->next;
	}
	return (med);
}

int		ft_isbuilt(t_lex *med, t_env *env)
{
	if (ft_strcmp(med->mem, "env") == 0)
	{
		//ft_env(med, env);
		return (0);
	}
	else if (ft_strcmp(med->mem, "setenv") == 0)
	{
		//ft_setenv(med, env);
		return (0);
	}
	else if (ft_strcmp(med->mem, "unsetenv") == 0)
	{
		//ft_unsetenv(med, env);
		return (0);
	}
	env = env + 0;
	return (1);
}

int		ft_child_molesting(char *line, t_env *env)
{
	t_lex	*med;
	t_pth	*pth;

	med = NULL;
	pth = NULL;
	med = ft_lexor(line);
	med = ft_rev_lex(med);
	if (ft_strcmp(med->mem, "exit") == 0)
		return (1);
	if (ft_isbuilt(med, env) == 0)
		return (0);
	med = ft_correction_facility(med);
	if (med == NULL)
		return (0);
	pth = ft_get_pth(pth, env);
	if (pth == NULL)
	{
		med = ft_free_lex(med);
		return (0);
	}
	med = ft_asign_path(pth, med);
	ft_muzukashi(med, env);
	ft_free_pth(pth);
	med = ft_free_lex(med);
	return (0);
}