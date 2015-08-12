/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/03 14:25:30 by mgras             #+#    #+#             */
/*   Updated: 2015/08/12 11:30:25 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_scan_error_one(int err_index, char *erro)
{
	if (err_index == 003)
	{
		ft_putstr("ERROR : \"");
		ft_putstr(C_CYAN);
		ft_putstr(erro);
		ft_putstr(C_RED);
		ft_putendl("\" : Another Op Sign after Op Sign");
	}
	else if (err_index == 004)
		ft_putendl("ERROR : \"PATH\" is Unset. Or not correctly managed.\
		Breaking all operations");
	else if (err_index == 005)
	{
		ft_putstr("ERROR : \"");
		ft_putstr(C_CYAN);
		ft_putstr(erro);
		ft_putstr(C_RED);
		ft_putendl("\" : is not a knowed command, Breaking all operations");
	}
}

void	ft_scan_error_two(int err_index, char *erro)
{
	if (err_index == 06)
	{
		ft_putendl("ERROR : Shit's fucked up man, you did it");
		ft_putendl("The error seems to be originated from this boy here");
		ft_putstr(C_CYAN);
		ft_putendl(erro);
		ft_putstr(C_RED);
		ft_putendl("If you're asking yourself, all your base has been stopped");
	}
}

void	ft_scann_eror(int err_index, char *erro)
{
	ft_putstr(C_RED);
	if (err_index == 001)
	{
		ft_putstr("ERROR : \"");
		ft_putstr(C_CYAN);
		ft_putstr(erro);
		ft_putstr(C_RED);
		ft_putendl("\" : No closing braces");
	}
	else if (err_index == 002)
	{
		ft_putstr("ERROR : \"");
		ft_putstr(C_CYAN);
		ft_putstr(erro);
		ft_putstr(C_RED);
		ft_putendl("\" : Nothing after Op Sign");
	}
	ft_scan_error_one(err_index, erro);
	ft_scan_error_two(err_index, erro);
	ft_putstr(C_NONE);
}
