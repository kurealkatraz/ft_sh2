/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prex_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/12 12:08:53 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 12:09:15 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_return_path_bin(char *med)
{
	if (access(med, F_OK) == -1)
	{
		ft_putstr(C_RED);
		ft_putstr("Error : ");
		ft_putstr(C_BLUE);
		ft_putstr(med);
		ft_putstr(C_RED);
		ft_putendl(" is not valid");
		return (NULL);
	}
	return (med);
}

char	*ft_make_bin(t_lex *med)
{
	char	*str;

	str = NULL;
	if (ft_ispath(med->mem))
		return (ft_return_path_bin(med->mem));
	if (!med->path)
		return (NULL);
	str = (char*)malloc(sizeof(char) * (ft_strlen(med->mem)
		+ ft_strlen(med->path) + 1));
	ft_strcpy(str, med->path);
	ft_strcat(str, "/");
	ft_strcat(str, med->mem);
	return (str);
}

char	**ft_envp_dup(t_env *env, int i)
{
	char	**envp;
	t_env	*swap;
	int		len;

	envp = (char**)malloc(sizeof(char*) * (i + 1));
	envp[i + 1] = NULL;
	swap = env;
	i = 0;
	while (swap != NULL)
	{
		len = ft_strlen(swap->value) + ft_strlen(swap->name) + 2;
		envp[i] = (char*)malloc(sizeof(char) * len);
		envp[i] = ft_strcpy(envp[i], swap->name);
		envp[i] = ft_strcat(envp[i], "=");
		envp[i] = ft_strcat(envp[i], swap->value);
		i++;
		envp[i] = NULL;
		swap = swap->next;
	}
	return (envp);
}

char	**ft_get_envp(t_env *env)
{
	char	**envp;
	t_env	*swap;
	int		i;

	swap = env;
	i = 0;
	if (swap == NULL)
		return (NULL);
	while ((swap = swap->next) != NULL)
		i++;
	envp = ft_envp_dup(env, i);
	return (envp);
}

char	**ft_make_argv(t_lex *med)
{
	t_lex	*swp;
	char	**argv;
	int		size;

	argv = NULL;
	swp = med;
	size = ft_is_what_len(med);
	argv = (char**)malloc(sizeof(char*) * (size) + 1);
	swp = med;
	size = 0;
	while (swp != NULL && !ft_iscompl(swp->mem[0]))
	{
		argv[size] = (char*)malloc(sizeof(char) * ft_strlen(swp->mem) + 1);
		argv[size] = ft_strcpy(argv[size], swp->mem);
		argv[++size] = NULL;
		swp = swp->next;
	}
	return (argv);
}
