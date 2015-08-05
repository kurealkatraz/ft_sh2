/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/04 18:23:09 by mgras             #+#    #+#             */
/*   Updated: 2015/08/05 12:05:23 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lex *ft_get_here(t_lex *med)
{
  t_lex *swp;

  swp = med;
  while (!ft_isredi(swp->mem[0]))
    swp = swp->next;
  return (swp->next);
}

t_lex *ft_solo_heredocs(t_lex *med)
{
  char  *line;
  t_lex *here;
  t_lex *swp;

  here = NULL;
  swp = ft_get_here(med);
  ft_putstr("NOTheredocs>");
  ft_get_next_line(0, &line);
  while (ft_strcmp(swp->mem, line))
  {
    ft_putstr("NOTheredocs>");
    ft_get_next_line(0, &line);
    if (ft_strcmp(med->mem, line))
      here = ft_new_meme(here, line);
  }
  return (here);
}

void ft_nice_meme(char *f_line)
{
  int   fd;

  ft_mkfile("/tmp/minishell_here_stock");
  fd = open("/tmp/minishell_here_stock", O_RDWR);
  ft_putstr_fd(f_line, fd);
  close(fd);
}

void ft_top_kek(t_lex *med, t_env *env)
{
  pid_t child;
  char  **argv;
  char  **envp;
  char  *bin;
  int   sys;

  child = fork();
  if (!child)
  {
    envp = ft_cre_exec(&bin, &argv, med, env);
    dup2(open("/tmp/minishell_here_stock", O_RDWR), 0);
    execve(bin, argv, envp);
    ft_del_exec(&bin, &argv, &envp);
  }
  else
    wait(&sys);
}

void ft_print_here(t_lex *here, t_lex *med, t_env *env)
{
  t_lex   *h_swp;
  int     len;
  char    *f_line;

  h_swp = here;
  while (h_swp)
  {
    len = len + 1 + ft_strlen(h_swp->mem);
    h_swp = h_swp->next;
  }
  f_line = (char*)malloc(sizeof(char) * (len + 1));
  h_swp = here;
  while (h_swp)
  {
    ft_strcat(f_line, h_swp->mem);
    ft_strcat(f_line, "\n");
    h_swp= h_swp->next;
  }
  f_line[len + 1] = '\0';
  ft_nice_meme(f_line);
  ft_strdel(&f_line);
  ft_top_kek(med, env);
}

void	ft_left_d_redi(t_lex *med, t_lex *curr, t_env *env)
{
  t_lex *here_store;
  t_lex *h_swp;

  here_store = ft_solo_heredocs(curr);
  h_swp = here_store;
  curr = ft_get_here(med);
  if (curr == med)
    while (h_swp)
    {
      ft_putendl(h_swp->mem);
      h_swp = h_swp->next;
    }
  else
    ft_print_here(h_swp, med, env);
  ft_free_lex(here_store);
}
