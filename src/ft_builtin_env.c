/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 18:31:44 by mgras             #+#    #+#             */
/*   Updated: 2015/03/25 17:14:24 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_get_index(char **argv)
{
	int		i;
	int		j;

	i = 2;
	while (argv[i] != NULL)
	{
		j = 1;
		while (argv[i][j] != '\0' && argv[i][j] != '=')
			j++;
		if (argv[i][j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_make_argv(char **argv, int i)
{
	int		size;
	char	**fresh;
	int		j;

	j = 0;
	while (argv[j] != NULL)
		j++;
	size = j - (i - 2);
	fresh = (char**)malloc(sizeof(char*) * size);
	j = 0;
	while (argv[i] != NULL)
		fresh[j++] = ft_strdup(argv[i++]);
	fresh[j] = NULL;
	return (fresh);
}

t_env	*ft_env_i(char **argv, t_env *env)
{
	char	*path;
	int		i;
	t_env	*base;
	char	**arg;

	if ((i = ft_get_index(argv)) == -1)
	{
		ft_bellatrix_cuddlecunt(argv);
		return (env);
	}
	if ((path = ft_find_bin(argv[i], env)) == NULL)
	{
		ft_putstr("nope\n");
		return (env);
	}
	arg = ft_make_argv(argv, i);
	base = ft_env_generator(NULL, argv, i);
	ft_new_process(path, arg, base);
	base = ft_free_all_env(base);
	free(path);
	return (env);
}
