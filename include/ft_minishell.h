/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 15:34:46 by mgras             #+#    #+#             */
/*   Updated: 2015/03/25 17:12:24 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# define BUF_SIZE 42

# include "colors.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <limits.h>
# include <time.h>

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_pth
{
	char			*path;
	struct s_pth	*next;
}					t_pth;

/*
**	ft_errors.c
*/
void				e_no_match_env(char *erred_str);
void				e_no_such_path(char *erred_str);

/*
**	ft_0_free.c
*/
void				ft_free_argv(char **argv);
t_env				*ft_free_member(t_env *current, t_env *saved);
t_env				*ft_free_all_env(t_env *env);

/*
**	ft_builtin_gmb.c
*/
void				ft_cd_errors(int index, char *erred);
t_env				*ft_home_cd(t_env *env);
t_env				*ft_maj_pwd(t_env *env);
t_env				*ft_maj_old(t_env *env);

/*
** ft_builtin_env.c
*/
int					ft_get_index(char **argv);
char				**ft_make_argv(char **argv, int i);
t_env				*ft_env_i(char **argv, t_env *env);

/*
**	ft_builtin_fnc.c
*/
t_env				*ft_setenv(t_env *env, char *mod);
t_env				*ft_unsetenv(t_env *env, char *mod);
t_env				*ft_oldpwd(t_env *env);
t_env				*ft_cd(t_env *env, char *dir);

/*
**	ft_builtin_utility.c
*/
int					ft_is_builtin(char *name);
t_env				*ft_builtin(char **argv, t_env *env);
t_env				*ft_builtin_env(char **argv, t_env *env);

/*
**	ft_check_argv.c
*/
int					ft_check_setenv(char *arg);

/*
**	ft_child_abuse.c
*/
char				*ft_split_path(char *value);
t_pth				*ft_new_pth(t_pth *pth, char *path);
t_pth				*ft_get_pth(t_pth *pth, t_env *env);
void				ft_free_pth(t_pth *pth);

/*
**	ft_cleaner.c
*/
void				ft_free_pth(t_pth *pth);
char				*ft_clear_pth(t_pth *save, t_pth *curr);
int					ft_clean_len(char *dirty_pleb);
char				*ft_clean_str(char *dirty_pleb);

/*
**	ft_colors.c
*/
char				*ft_getend(char *dst, char *src, int j);
char				*ft_getpath(void);
char				*ft_gettime(void);
char				*ft_getname(char **envp);
void				ft_colors(char **envp);

/*
**	ft_core.c
*/
t_env				*ft_core(char *line, t_env *env);
void				ft_prompt(char **envp, t_env *env);
t_env				*shlvl_pp(t_env *env);

/*
**	ft_env.c
*/
char				**ft_get_envp(t_env *env);
t_env				*ft_new_env(t_env *env, char *full);
t_env				*ft_get_env(t_env *env, char **envp);

/*
**	ft_env_care.c
*/
t_env				*ft_minimal_env_gen(t_env *env);
t_env				*ft_env_generator(t_env *env, char **med, int markpos);

/*
**	gut_nuxt_lune.su
*/
char				*ft_fill_holder(int fd);
int					ft_get_next_line(int fd, char **line);

/*
**	ft_new_process.c
*/
char				*ft_split_path(char *value);
t_pth				*ft_new_pth(t_pth *pth, char *path);
t_pth				*ft_get_pth(t_pth *pth, t_env *env);
char				*ft_find_bin(char *bin, t_env *env);
void				ft_new_process(char *path, char **argv, t_env *env);

/*
**	ft_vorpalblade_snickersnack.c
*/
int					ft_bentobox_sushisnatch(char **argv, char *cmp, int pos);
void				ft_bellatrix_cuddlecunt(char **argv);

#endif
