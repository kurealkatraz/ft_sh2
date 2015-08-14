/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 14:29:11 by mgras             #+#    #+#             */
/*   Updated: 2015/08/14 13:20:38 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# define BUF_SIZE 42
# define BUFF_SIZE 42

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
# include <sys/types.h>
# include <sys/uio.h>

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
**	ft_get_file.c
*/
int					error(char **holder);
int					ft_get_file(const int fd, char **line);

/*
**	ft_setenv.c
*/
void				ft_usrenv_error(char *err, int mol);
int					ft_comp_env_str(t_env *env, char *str);
t_lex				*ft_check_usenv(t_lex *med, t_env *env);
void				ft_put_at_end_env(t_env *env, char *full);
t_env				*ft_setenv(t_lex *med, t_env *env);

/*
**	ft_prex.c
*/
t_env				*ft_muzukashi(t_lex *med, t_env *env);

/*
**	ft_prex_one.c
*/
char				*ft_return_path_bin(char *med);
char				*ft_make_bin(t_lex *med);
char				**ft_envp_dup(t_env *env, int i);
char				**ft_get_envp(t_env *env);
char				**ft_make_argv(t_lex *med);

/*
**	ft_prex_two.c
*/
t_lex				*ft_next_op(t_lex *med);
void				ft_exec(char **envp, char **argv, char *bin);
char				*ft_get_redi_dir(t_lex *med);
char				*ft_get_redi(t_lex *med);
void				ft_mkfile(char *filename);

/*
**	ft_prex_three.c
*/
int					ft_is_op_redi(t_lex *med);
void				ft_right_d_redi(t_lex *med, t_env *env);
void				ft_right_s_redi(t_lex *med, t_env *env);
int					ft_reboot_file(int fd, t_lex *med);
void				ft_delfile(char *filename);

/*
**	ft_prex_four.c
*/
t_lex				*ft_get_next_op(t_lex *med);
t_env				*ft_what_buildtin(t_lex *med, t_env *env);
char				**ft_cre_exec\
						(char **bin, char ***argv, t_lex *med, t_env *env);
void				ft_del_exec(char **bin, char ***argv, char ***envp);
t_lex				*ft_get_fd_s_redi(t_lex *med);

/*
**	ft_prex_five.c
*/
void				ft_prex_errors(char *erstr, int erono);
void				ft_left_s_redi(t_lex *med, t_env *env);
t_lex				*ft_check_if_more(t_lex *med);
t_env				*ft_parser_split(t_lex *med, t_lex *swp, t_env *env);
t_env				*ft_parser(t_lex *med, t_env *env);

/*
**	ft_path_maker.c
*/
char				*ft_split_path(char *value);
t_pth				*ft_new_pth(t_pth *pth, char *path);
t_pth				*ft_get_pth(t_pth *pth, t_env *env);
void				ft_free_pth(t_pth *pth);

/*
**	ft_cleaner.c
*/
char				*ft_cstr_split1\
						(char *clean_pleb, char *dirty_pleb, int *ts, int *ss);
char				*ft_cstr_split2\
						(char *clean_pleb, char *dirty_pleb, int *ts, int *ss);
char				*ft_cstr_split3\
						(char *clean_pleb, char *dirty_pleb, int *ts, int *ss);
char				*ft_clean_str(char *dirty_pleb);

/*
**	ft_cleaner_one.c
*/
void				ft_clean_split1(char *dirty_pleb, int *swipe, int *len);
void				ft_clean_split2(char *dirty_pleb, int *swipe, int *len);
void				ft_clean_split3(char *dirty_pleb, int *swipe, int *len);
int					ft_clean_len(char *dirty_pleb);

/*
**	ft_color.c
*/
char				*ft_getend(char *dst, char *src, int j);
char				*ft_getpath(void);
char				*ft_gettime(void);
char				*ft_getname(char **envp);
void				ft_colors(char **envp);

/*
**	ft_core.c
*/
t_env				*shlvl_pp(t_env *env);
t_env				*ft_get_min_env(t_env *env);

/*
**	ft_core_one.c
*/
int					ft_get_proper_len(char *line, int ts, int ss);
char				*ft_split_line(char *line, int *ss, int len, int ts);
t_env				*ft_core(char *line, t_env *env, int *ext);
void				ft_prompt(char **envp, t_env *env);

/*
**	ft_env.c
*/
t_env				*ft_free_one_env(t_env *env);
t_env				*ft_del_env(t_env *env, t_env *del);
t_env				*ft_new_env(t_env *env, char *full);
t_env				*ft_get_env(t_env *env, char **envp);

/*
**	ft_env_one.c
*/
void				ft_print_env(t_env *env);
t_env				*ft_make_usr_env(t_env *env, t_lex *med);
t_env				*ft_free_usr_env(t_env *env, t_lex *med);
void				ft_print_env_usr(t_env *env, t_lex *med);
int					ft_lex_env(t_lex *med);

/*
**	ft_env_two.c
*/
int					ft_ret_parse_env(int change, t_lex *med);
int					ft_parse_env(t_lex *med, int change, int index);
void				ft_commit_env_changes(t_lex *med, int nb);
t_env				*ft_env(t_lex *med, t_env *env);
t_lex				*ft_get_exec(t_lex *med);

/*
**	ft_env_three.c
*/
int					ft_env_noexec(t_lex *med);
t_lex				*ft_del_lex_mem(t_lex *prev, t_lex *curr);

/*
**	get_next_line.c
*/
char				*ft_fill_holder(int fd);
int					ft_get_next_line(int fd, char **line);

/*
**	ft_lexseur.c
*/
t_lex				*ft_compl_lex(int *s, char *line, t_lex *med);
t_lex				*ft_singlebrace(t_lex *med, char q);
t_lex				*ft_braced_lex(int *s, char *line, t_lex *med, char q);
t_lex				*ft_next_lex(t_lex *med, int *s, char *line);
t_lex				*ft_lexor(char *line);

/*
**	ft_lexseur_one.c
*/
t_lex				*ft_alpha_lex(int *s, char *line, t_lex *med);

/*
**	ft_chldabs
*/
t_lex				*ft_get_bin(t_lex *med, t_pth *pth);
t_lex				*ft_asign_path(t_pth *pth, t_lex *med);
t_env				*ft_free_all_env(t_env *env);
t_env				*ft_child_molesting(char *line, t_env *env, int *ext);

/*
**	ft_lex_mcr.c
*/
t_lex				*ft_free_lex(t_lex *medivac);
t_lex				*ft_new_meme(t_lex *med, char *meme);
t_lex				*ft_rev_lex(t_lex *medivac);

/*
**	ft_iswhat.c
*/
int					ft_is_what_len_pipe(t_lex *med);
int					ft_is_next_op_pipe(t_lex *med);

/*
**	ft_iswhat_one.c
*/
int					ft_is_env_dubs(t_env *env, t_lex *med);
int					ft_ispipe(char c);
int					ft_is_dubs(t_lex *med);
int					ft_is_buildtin(char *str);
int					ft_isenvmem(char *str);

/*
**	ft_iswhat_two.c
*/
int					ft_ispath(char *str);
int					ft_isredi(char c);
int					ft_isalien(char c);
int					ft_iscompl(char c);
int					ft_is_what_len(t_lex *med);

/*
**	ft_correction_center.c
*/
t_lex				*ft_comp_scan(t_lex *med);
t_lex				*ft_braced_scan(t_lex *med, char brace);
t_lex				*ft_scaner(t_lex *med);
t_lex				*ft_correction_facility(t_lex *med);

/*
**	ft_scan_error.c
*/
void				ft_scan_error_one(int err_index, char *erro);
void				ft_scan_error_two(int err_index, char *erro);
void				ft_scann_eror(int err_index, char *erro);

/*
**	ft_unsetenv.c
*/
char				*ft_strcdup(char *str, char c);
void				ft_usrunenv_error(char *err, int mol);
t_lex				*ft_check_usunenv(t_lex *med, t_env *env);
t_env				*ft_get_del_env(char *mol, t_env *env);
t_env				*ft_unsetenv(t_lex *med, t_env *env);

/*
**	ft_cd.c
*/
void				ft_uscderror(char *err, int mol);
t_env				*ft_cd_prev(t_lex *med, t_env *env);
t_env				*ft_cd_usr(t_lex *med, t_env *env);
t_env				*ft_cd_home(t_env *env);
t_env				*ft_cd(t_lex *med, t_env *env);

/*
**	ft_pipes.c
*/
int					ft_start_pipe(char **argv, char **envp, char *bin);
int					ft_rec_pipe(char **argv, char **envp, char *bin, int src);
int					ft_end_pipe(char **argv, char **envp, char *bin, int src);
t_lex				*ft_pipe_it(t_lex *med, t_env *env, int fd);

/*
**	ft_pipes_one.c
*/
t_lex				*ft_print_lex(t_lex *med);
char				**ft_del_tab(char **argv);
t_lex				*ft_get_end_of_pipe(int fd);
char				**ft_print_raw_tab_fd(char **tab, int fd);
char				**ft_print_tab(char **tab);

/*
**	ft_pipes_two.c
*/
char				**ft_make_read(int fd);
t_lex				*ft_get_added(int fd, t_lex *added);
int					ft_s_r_redi_init(t_lex *med);
int					ft_s_r_redi_p(char **argv, char **envp, t_lex *swp, int fd);

/*
**	ft_pipes_three.c
*/
int					ft_d_r_redi_p(char **argv, char **envp, t_lex *swp, int fd);
int					ft_d_r_redi_init(t_lex *med);

/*
**	ft_heredocs.c
*/
void				ft_nice_meme(char *f_line);
t_lex				*ft_solo_heredocs(t_lex *med);
t_lex				*ft_get_here(t_lex *med);

/*
**	ft_heredocs_one.c
*/
void				ft_print_here(t_lex *here, t_lex *med, t_env *env);
void				ft_top_kek(t_lex *med, t_env *env);
void				ft_left_d_redi(t_lex *med, t_lex *curr, t_env *env);

#endif
