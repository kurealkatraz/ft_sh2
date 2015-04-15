/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/13 21:24:27 by mgras             #+#    #+#             */
/*   Updated: 2015/04/13 22:06:12 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_whatredi(t_lex *med)
{
	t_lex *swp;

	swp = med;
	while (swp != NULL)
	{
		if (ft_isredi(swp->mem[0]))
		{
			if (swp->next != NULL)
				return (1);
			else
				return (-1);
		}
		swp = swp->next;
	}
	return (-1);
}

int		ft_check_pipe(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	if (swp->mem[0] == '|')
		return (-1);
	while (swp != NULL)
	{
		if (swp->mem[0] == '|')
		{
			if (ft_iscompl(swp->next->mem[0]))
				return (2);
			else
				return (-1);
		}
	}
	return (-1);
}

int		ft_parseur(t_lex *med)
{
	t_lex	*swp;

	swp = med;
	while (swp != NULL)
	{
		if (ft_isredi(swp[0]))
			return (ft_whatredi(med));
		else if (swp[0] == '|')
			return (ft_check_pipe(med))
		swp = swp->next;
	}
	return (0);
}