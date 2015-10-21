/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chldabs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/31 18:05:14 by mgras             #+#    #+#             */
/*   Updated: 2015/10/21 12:07:46 by mgras            ###   ########.fr       */
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
	t_lex	*mwp;

	mwp = med;
	while (mwp != NULL)
	{
		if (!ft_ispath(mwp->mem) && !ft_isenvmem(mwp->mem)\
		&& !(ft_isalien(mwp->mem[0])))
			mwp = ft_get_bin(mwp, pth);
		else
			mwp->path = NULL;
		mwp = mwp->next;
	}
	return (med);
}

t_env	*ft_free_all_env(t_env *env)
{
	t_env	*swp;

	swp = env;
	while (swp != NULL)
	{
		swp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = swp;
	}
	return (NULL);
}

t_env	*ft_child_molesting(char *line, t_env *env, int *ext)
{
	t_lex	*med;
	t_pth	*pth;

	med = NULL;
	pth = NULL;
	med = ft_lexor(line);
	med = ft_rev_lex(med);
	pth = ft_get_pth(pth, env);
	if (pth != NULL)
		med = ft_asign_path(pth, med);
	ft_free_pth(pth);
	if (!med)
		return (env);
	if (ft_strcmp(med->mem, "exit") == 0 || med->mem[0] == 4)
	{
		*ext = 1;
		return (ft_free_all_env(env));
	}
	med = ft_correction_facility(med);
	if (med == NULL)
		return (env);
	env = ft_muzukashi(med, env);
	if (med)
		med = ft_free_lex(med);
	return (env);
}
