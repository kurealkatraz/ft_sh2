/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prex_five.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/12 12:16:49 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 12:17:05 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_prex_errors(char *erstr, int erono)
{
	ft_putstr(C_RED);
	if (erono == 001)
	{
		ft_putstr("ERROR : \"");
		ft_putstr(C_CYAN);
		ft_putstr(erstr);
		ft_putstr(C_RED);
		ft_putendl("\" : is not Valid");
	}
	ft_putstr(C_NONE);
}

void	ft_left_s_redi(t_lex *med, t_env *env)
{
	char		**argv;
	char		**envp;
	char		*bin;
	pid_t		child;
	int			fd;

	child = fork();
	fd = 0;
	if (child == 0)
	{
		envp = ft_cre_exec(&bin, &argv, med, env);
		fd = open(ft_get_fd_s_redi(med)->mem, O_RDONLY);
		if (fd != -1 && dup2(fd, 0) != -1)
		{
			execve(bin, argv, envp);
			ft_del_exec(&bin, &argv, &envp);
		}
		else
			ft_prex_errors(ft_get_fd_s_redi(med)->mem, 001);
		kill(getpid(), SIGKILL);
	}
	else
		wait(&fd);
}

t_lex	*ft_check_if_more(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (swp)
	{
		if (swp->path || ft_is_buildtin(swp->mem))
			return (med);
		swp = swp->next;
	}
	return (NULL);
}

t_env	*ft_parser_split(t_lex *med, t_lex *swp, t_env *env)
{
	if (ft_strcmp(">", ft_get_redi(swp)) == 0)
		ft_right_s_redi(swp, env);
	else if (ft_strcmp(">>", ft_get_redi(swp)) == 0)
		ft_right_d_redi(swp, env);
	else if (ft_strcmp("<", ft_get_redi(swp)) == 0)
		ft_left_s_redi(swp, env);
	else if (ft_strcmp("<<", ft_get_redi(swp)) == 0)
		ft_left_d_redi(med, swp, env);
	else
		return (env);
	return (env);
}

t_env	*ft_parser(t_lex *med, t_env *env)
{
	t_lex	*swp;

	swp = med;
	while (swp != NULL)
	{
		if (ft_is_op_redi(swp))
			ft_parser_split(med, swp, env);
		else if (ft_is_next_op_pipe(swp))
			swp = ft_pipe_it(swp, env, -2);
		else if (ft_is_buildtin(swp->mem))
			env = ft_what_buildtin(swp, env);
		else if (ft_get_del_env("PATH", env) == NULL)
			return (NULL);
		else
			ft_exec(ft_get_envp(env), ft_make_argv(swp), ft_make_bin(swp));
		swp = ft_get_next_op(swp);
		swp = ft_check_if_more(swp);
	}
	return (env);
}
