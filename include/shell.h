/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 14:29:11 by mgras             #+#    #+#             */
/*   Updated: 2015/04/17 17:44:48 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# define BUF_SIZE 42

# include "colors.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <limits.h>
# include <time.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_lex
{
	char			*mem;
	char			*path;
	struct s_lex	*next;
}					t_lex;

typedef struct		s_pth
{
	char			*path;
	struct s_pth	*next;
}					t_pth;

/*
**	ft_setenv.c
*/
void	ft_usrenv_error(char *err, int mol);
int		ft_comp_env_str(t_env *env, char *str);
t_lex	*ft_exist_env(t_env *env, t_lex *med);
t_lex	*ft_check_usenv(t_lex *med, t_env *env);
t_env   *ft_setenv(t_lex *med, t_env *env);

/*
**	ft_prex.c
*/
t_lex	*ft_get_next_op(t_lex *med);
char	*ft_make_bin(t_lex *med);
char	**ft_get_envp(t_env *env);
char	**ft_make_argv(t_lex *med);
t_lex	*ft_next_op(t_lex *med);
void	ft_exec(char **envp, char **argv, char *bin);
t_env	*ft_parser(t_lex *med, t_env *env);
t_env	*ft_muzukashi(t_lex *med, t_env *env);

/*
**	ft_path_macker.c
*/
char	*ft_split_path(char *value);
t_pth	*ft_new_pth(t_pth *pth, char *path);
t_pth	*ft_get_pth(t_pth *pth, t_env *env);
void	ft_free_pth(t_pth *pth);

/*
**	ft_cleaner.c
*/
int		ft_clean_len(char *dirty_pleb);
char	*ft_clean_str(char *dirty_pleb);

/*
**	ft_color.c
*/
char	*ft_getend(char *dst, char *src, int j);
char	*ft_getpath(void);
char	*ft_gettime(void);
char	*ft_getname(char **envp);
void	ft_colors(char **envp);

/*
**	ft_core.c
*/
t_env	*ft_core(char *line, t_env *env, int *ext);
void	ft_prompt(char **envp, t_env *env);
t_env	*shlvl_pp(t_env *env);

/*
**	ft_env.c
*/
void	ft_print_env(t_env *env);
t_env	*ft_make_usr_env(t_env *env, t_lex *med);
t_env	*ft_free_one_env(t_env	*env);
t_env	*ft_free_usr_env(t_env *env, t_lex *med);
void	ft_print_env_usr(t_env *env, t_lex *med);
int		ft_lex_env(t_lex *med);
int		ft_env_noexec(t_lex *med);
t_lex	*ft_del_lex_mem(t_lex *prev, t_lex *curr);
void	ft_commit_env_changes(t_lex *med, int nb);
int		ft_parse_env(t_lex *med);
t_env	*ft_env(t_lex *med, t_env *env);
t_env	*ft_new_env(t_env *env, char *full);
t_env	*ft_get_env(t_env *env, char **envp);
t_lex	*ft_free_single_lex(t_lex *med);
t_env	*ft_del_env(t_env *env, t_env *del);

/*
**	get_next_line.c
*/
char	*ft_fill_holder(int fd);
int		ft_get_next_line(int fd, char **line);

/*
**	lexseur.c
*/
t_lex	*ft_alpha_lex(int *s, char *line, t_lex *med);
t_lex	*ft_compl_lex(int *s, char *line, t_lex *med);
t_lex	*ft_braced_lex(int *s, char *line, t_lex *med, char q);
t_lex	*ft_next_lex(t_lex *med, int *s, char *line);
t_lex	*ft_lexor(char *line);

/*
**	ft_chldabs
*/
t_env	*ft_free_all_env(t_env *env);
t_env	*ft_child_molesting(char *line, t_env *env, int *ext);

/*
**	ft_lex_mcr.c
*/
t_lex	*ft_free_lex(t_lex *medivac);
t_lex	*ft_new_meme(t_lex *med, char *meme);
t_lex	*ft_rev_lex(t_lex *medivac);

/*
**	ft_iswhat.c
*/
int		ft_is_what_len_pipe(t_lex *med);
int		ft_is_what_len(t_lex *med);
int		ft_ispipe(char c);
int		ft_is_next_op_pipe(t_lex *med);
int		ft_iscompl(char c);
int		ft_isalien(char c);
int		ft_isredi(char c);
int		ft_ispath(char *str);
int		ft_isenvmem(char *str);
int		ft_is_buildtin(char *str);
int		ft_is_dubs(t_lex *med);
int		ft_is_env_dubs(t_env *env, t_lex *med);

/*
**	ft_correction_center.c
*/
t_lex	*ft_comp_scan(t_lex *med);
t_lex	*ft_braced_scan(t_lex *med, char brace);
t_lex	*ft_scaner(t_lex *med);
t_lex	*ft_correction_facility(t_lex *med);

/*
**	ft_scan_error.c
*/
void	ft_scann_eror(int err_index, char *erro);

/*
**	ft_unsetenv.c
*/
char	*ft_strcdup(char *str, char c);
void	ft_usrunenv_error(char *err, int mol);
t_lex	*ft_check_usunenv(t_lex *med, t_env *env);
t_env	*ft_get_del_env(char *mol, t_env *env);
t_env	*ft_unsetenv(t_lex *med, t_env *env);

/*
**	ft_cd.c
*/
void	ft_uscderror(char *err, int mol);
t_env	*ft_cd_prev(t_lex *med, t_env *env);
t_env	*ft_cd_usr(t_lex *med, t_env *env);
t_env	*ft_cd(t_lex *med, t_env *env);

/*
**	ft_pipes.c
*/
char	**ft_make_pipe_argv(t_lex *med, t_lex *added);
char	**ft_del_tab(char **argv);
t_lex	*ft_get_end_of_pipe(int	fd);
t_lex	*ft_pipe_it(t_lex *med, t_env *env);

#endif
