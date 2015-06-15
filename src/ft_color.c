/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 16:48:29 by mgras             #+#    #+#             */
/*   Updated: 2015/04/02 15:22:47 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_getend(char *dst, char *src, int j)
{
	int		i;
	int		k;

	i = ft_strlen(src);
	k = j;
	while (k - j < 3)
		j -= (src[i--] == '/' ? 1 : 0);
	i++;
	dst = ft_strncpy(dst, src + i, ft_strlen(src + i));
	return (dst);
}

char	*ft_getpath(void)
{
	char	*fresh;
	char	*buff;
	int		i;
	int		j;

	if (!(buff = getcwd(NULL, 0)) ||
			!(fresh = (char*)malloc(sizeof(char) * (ft_strlen(buff) + 1))))
		return (ft_strdup("You did not just did this. You wicked devil."));
	i = ft_strlen(buff);
	j = 0;
	while (i > 0)
		j += (buff[i--] == '/') ? 1 : 0;
	if (j < 3)
		fresh = ft_strncpy(fresh, buff, ft_strlen(buff));
	else
		fresh = ft_getend(fresh, buff, j);
	free(buff);
	return (fresh);
}

char	*ft_gettime(void)
{
	char	t[26];
	time_t	tloc;

	time(&tloc);
	ft_strcpy(t, ctime(&tloc));
	return (ft_strndup(t + 11, 8));
}

char	*ft_getname(char **envp)
{
	int		i;
	char	*fresh;

	i = 0;
	if (!envp)
		return (ft_strdup("Anon"));
	while ((envp[i] != NULL) && 0 != ft_strncmp(envp[i], "LOGNAME", 7))
		i++;
	if (envp[i] == NULL)
		fresh = ft_strdup("Anon");
	else
		fresh = ft_strdup(envp[i] + 8);
	return (fresh);
}

void	ft_colors(char **envp)
{
	char	*name;
	char	*time;
	char	*path;

	time = ft_gettime();
	name = ft_getname(envp);
	path = ft_getpath();
	ft_putstr(C_CYAN);
	ft_putstr(name);
	ft_putstr(C_RED);
	ft_putstr(" - ");
	ft_putstr(C_GREEN);
	ft_putstr(time);
	ft_putstr(C_RED);
	ft_putstr(" - ");
	ft_putstr(C_MAGENTA);
	ft_putstr(path);
	ft_putstr(" : ");
	ft_putstr(C_NONE);
	free(path);
	free(name);
	free(time);
}
