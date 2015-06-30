/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/07 18:49:25 by mgras             #+#    #+#             */
/*   Updated: 2015/04/17 14:16:33 by mgras            ###   ########.fr       */
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
	if (swap == NULL)
		return (NULL);
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

char	*ft_get_redi_dir(t_lex *med)
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
	return (swp->mem);
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
		if ((fd = open(ft_get_redi_dir(med), O_WRONLY)) < 0)
		{
			ft_mkfile(ft_get_redi_dir(med));
			if ((fd = open(ft_get_redi_dir(med), O_WRONLY)) < 0)
			{
				ft_scann_eror(006, ft_get_redi_dir(med));
				kill(getpid(), SIGKILL);
			}
		}
		else
		{
			close (fd);
			ft_delfile(ft_get_redi_dir(med));
			ft_mkfile(ft_get_redi_dir(med));
			fd = open(ft_get_redi_dir(med), O_RDWR);
		}
		dup2(fd, 1);
		ft_exec(ft_get_envp(env), ft_make_argv(med), ft_make_bin(med));
		close(fd);
		kill(getpid(), SIGKILL);
	}
	wait(&sys);
}

void	ft_right_d_redi(t_lex *med, t_env *env)
{
	pid_t	child;
	int		sys;
	int		fd;

	child = fork();
	if (child == 0)
	{
		if ((fd = open(ft_get_redi_dir(med), O_WRONLY | O_APPEND)) < 0)
		{
			ft_mkfile(ft_get_redi_dir(med));
			if ((fd = open(ft_get_redi_dir(med), O_WRONLY | O_APPEND)) < 0)
			{
				ft_scann_eror(006, ft_get_redi_dir(med));
				kill(getpid(), SIGKILL);
			}
		}
		dup2(fd, 1);
		ft_exec(ft_get_envp(env), ft_make_argv(med), ft_make_bin(med));
		close(fd);
		kill(getpid(), SIGKILL);
	}
	wait(&sys);
}

int		ft_is_op_redi(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (swp)
	{
		if (ft_isredi(swp->mem[0]))
			return (1);
		swp = swp->next;
	}
	return (0);
}

t_lex	*ft_get_next_op(t_lex *med)
{
	t_lex	*swp;

	if (med == NULL)
		return (med);
	swp = med;
	{
		while (!ft_iscompl(swp->mem[0]))
		{
			swp = swp->next;
			if (swp == NULL)
				return (swp);
			else if (ft_iscompl(swp->mem[0]))
				swp = ft_get_next_op(swp->next);
			if (swp == NULL)
				return (swp);
		}
	}
	return (swp->next);
}

t_env	*ft_what_buildtin(t_lex *med, t_env *env)
{
	if (ft_strcmp(med->mem, "env") == 0)
		env = ft_env(med, env);
	else if(ft_strcmp(med->mem, "setenv") == 0)
		env = ft_setenv(med, env);
	else if(ft_strcmp(med->mem, "unsetenv") == 0)
		env = ft_unsetenv(med, env);
	else if(ft_strcmp(med->mem, "cd") == 0)
		env = ft_cd(med, env);
	return (env);
}

void	ft_left_s_redi(t_lex *med, t_env *env)
{
	t_lex	*swp;
	int		sys;
	pid_t	child;
	int		fd;

	child = fork();
	if (child == 0)
	{
		swp = med;
		while (ft_strcmp("<",swp->mem) != 0)
			swp = swp->next;
		if (access(swp->next->mem, F_OK) == -1)
		{
			ft_putstr(C_RED);
			ft_putstr("no such file or directory ");
			ft_putstr(C_CYAN);
			ft_putendl(swp->next->mem);
			ft_putstr(C_NONE);
			kill(getpid(), SIGKILL);
		}
		swp = swp->next;
		fd = open(swp->mem, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(1, fd);
		ft_exec(ft_get_envp(env), ft_make_argv(med), ft_make_bin(med));
		close(fd);
		kill(getpid(), SIGKILL);
	}
	wait(&sys);
}

void	ft_left_d_redi(t_lex *med, t_env *env)
{
	t_lex	*swp;
	int		sys;
	pid_t	child;
	char	*str;
	t_lex	*here_holder;

	child = fork();
	str = NULL;
	here_holder = NULL;
	env = env + 0;
	sys = 0;
	sys = sys + 0;
	if (child == 0)
	{
		swp = med;
		while (ft_strcmp("<<", swp->mem) != 0)
			swp = swp->next;
		swp = swp ->next;
		while (ft_strcmp(str, swp->mem) != 0)
		{
			if (ft_get_next_line(1, &str) == 1)
				here_holder = ft_new_meme(here_holder, str);
		}
		here_holder = ft_rev_lex(here_holder);
		ft_free_lex(here_holder);
	}
	else
		wait(&sys);
}

t_env	*ft_parser(t_lex *med, t_env *env)
{
	t_lex	*swp;

	swp = med;
	while (swp != NULL)
	{
		if (ft_is_op_redi(swp))
		{
			if (ft_strcmp(">", ft_get_redi(swp)) == 0)
				ft_right_s_redi(swp, env);
			else if (ft_strcmp(">>", ft_get_redi(swp)) == 0)
				ft_right_d_redi(swp, env);
			else if (ft_strcmp("<", ft_get_redi(swp)) == 0)
				ft_left_s_redi(swp, env);
			else if (ft_strcmp("<<", ft_get_redi(swp)) == 0)
				ft_left_d_redi(swp, env);
			else
				return (env);
		}
		else if (ft_is_buildtin(swp->mem))
			env = ft_what_buildtin(swp, env);
		else if (ft_get_del_env("PATH", env) == NULL)
			return (NULL);
		else
			ft_exec(ft_get_envp(env), ft_make_argv(swp), ft_make_bin(swp));
		swp = ft_get_next_op(swp);
	}
	return (env);
}

t_env	*ft_muzukashi(t_lex *med, t_env *env)
{
	if (!ft_ispath(med->mem) && med->path == NULL && !ft_is_buildtin(med->mem))
		ft_scann_eror(005, med->mem);
	else
		env = ft_parser(med, env);
	return (env);
}
