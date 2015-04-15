/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/07 18:49:25 by mgras             #+#    #+#             */
/*   Updated: 2015/04/13 21:16:21 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_make_bin(t_lex *med)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * (ft_strlen(med->mem)
		+ ft_strlen(med->path) + 1));
	ft_strcpy(str, med->path);
	ft_strcat(str, "/");
	ft_strcat(str, med->mem);
	return (str);
}

char	**ft_get_envp(t_env *env)
{
	char	**envp;
	t_env	*swap;
	int		i;
	int		len;

	swap = env;
	i = 0;
	while ((swap = swap->next) != NULL)
		i++;
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

char	**ft_make_argv(t_lex *med)
{
	t_lex	*swp;
	char	**argv;
	int		size;

	argv = NULL;
	swp = med;
	size = 0;
	while (swp != NULL && !ft_iscompl(swp->mem[0]))
	{
		size++;
		swp = swp->next;
	}
	argv = (char**)malloc(sizeof(char*) * (size) + 1);
	swp = med;
	size = 0;
	while (swp != NULL && !ft_iscompl(swp->mem[0]))
	{
		argv[size] = (char*)malloc(sizeof(char) * ft_strlen(swp->mem) + 1);
		argv[size] = ft_strcpy(argv[size], swp->mem);
		size++;
		swp = swp->next;
	}
	return (argv);
}

t_lex	*ft_next_op(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (swp != NULL && !ft_iscompl(swp->mem[0]))
		swp = swp->next;
	if (swp)
		if (ft_iscompl(swp->mem[0]))
			swp = swp->next;
	return (swp);
}

void	ft_exec(char **envp, char **argv, char *bin)
{
	pid_t	child;
	int		sys;

	child = fork();
	if (child == 0)
	{
		execve(bin, argv, envp);
		kill(getpid(), SIGKILL);
	}
	else
		wait(&sys);
}

char	*ft_get_redi(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (!ft_isredi(swp->mem[0]) && swp)
		swp = swp->next;
	if (swp->next == NULL || swp == NULL)
	{
		ft_scann_eror(007, NULL);
		kill(getpid(), SIGKILL);
	}
	return (swp->next->mem);
}

void	ft_mkfile(char *filename)
{
	pid_t	child;
	int		sys;
	char	**argv;

	child = fork();
	argv = NULL;
	if (child == 0)
	{
		argv = (char**)malloc(sizeof(char*) * 3);
		argv[2] = NULL;
		argv[1] = (char*)malloc(sizeof(char) * ft_strlen(filename) + 1);
		argv[0] = (char*)malloc(sizeof(char) * ft_strlen("touch") + 1);
		ft_strcpy(argv[1], filename);
		ft_strcpy(argv[0], "touch");
		execve("/usr/bin/touch", argv, NULL);
		kill(getpid(), SIGKILL);
	}
	wait(&sys);
}
void	ft_delfile(char *filename)
{
	pid_t	child;
	int		sys;
	char	**argv;

	child = fork();
	argv = NULL;
	if (child == 0)
	{
		argv = (char**)malloc(sizeof(char*) * 4);
		argv[3] = NULL;
		argv[2] = (char*)malloc(sizeof(char) * ft_strlen(filename) + 1);
		argv[1] = (char*)malloc(sizeof(char) * ft_strlen("-rf") + 1);
		argv[0] = (char*)malloc(sizeof(char) * ft_strlen("touch") + 1);
		ft_strcpy(argv[2], filename);
		ft_strcpy(argv[1], "-rf");
		ft_strcpy(argv[0], "rm");
		execve("/bin/rm", argv, NULL);
		kill(getpid(), SIGKILL);
	}
	wait(&sys);	
}

void	ft_right_s_redi(t_lex *med, t_env *env)
{
	pid_t	child;
	int		sys;
	int		fd;

	child = fork();
	if (child == 0)
	{
		if ((fd = open(ft_get_redi(med), O_RDWR)) < 0)
		{
			ft_mkfile(ft_get_redi(med));
			if ((fd = open(ft_get_redi(med), O_RDWR)) < 0)
			{
				ft_scann_eror(006, ft_get_redi(med));
				kill(getpid(), SIGKILL);
			}
		}
		else
		{
			close (fd);
			ft_delfile(ft_get_redi(med));
			ft_mkfile(ft_get_redi(med));
			fd = open(ft_get_redi(med), O_RDWR);
		}
		dup2(fd, 1);
		ft_exec(ft_get_envp(env), ft_make_argv(med), ft_make_bin(med));
		close(fd);
		kill(getpid(), SIGKILL);
	}
	wait(&sys);
}

void	ft_muzukashi(t_lex *med, t_env *env)
{
	if (!ft_ispath(med->mem) && med->path == NULL)
	{
		ft_scann_eror(005, med->mem);
		return ;
	}
	ft_right_s_redi(med, env);
	env = env + 0;
}