/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 23:58:48 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/26 18:55:05 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_error(t_pars_error error)
{
	if (error.i == SPECIAL)
	{
		ft_putstr_fd("erreur de syntaxe près du symbole inattendu « ", 2);
		ft_putchar_fd(error.c, 2);
		ft_putstr_fd(" »\n", 2);
	}		
	if (error.i == REDIR || error.i == REDIR2)
	{
		ft_putstr_fd("erreur de syntaxe près du symbole inattendu « ", 2);
		if (error.i == REDIR2)
			ft_putstr_fd(error.str, 2);
		ft_putstr_fd(error.str, 2);
		ft_putstr_fd(" »\n", 2);
	}
	if (error.i == ERROR_MALLOC)
	{
		ft_putstr_fd("erreur d'allocation de memoire, fonction ", 2);
		ft_putstr_fd(error.str, 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	error_malloc(char *str)
{
	t_pars_error	error;

	error.i = ERROR_MALLOC;
	error.str = str;
	print_error(error);
}