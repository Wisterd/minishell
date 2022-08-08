/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 23:58:48 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/08 17:42:43 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_error(t_pars_error error)
{
	if (error.i == SPECIAL)
		printf("erreur de syntaxe près du symbole inattendu « %c »\n", error.c);
	if (error.i == REDIR)
		printf("erreur de syntaxe près du symbole inattendu « %s »\n", error.str);
	if (error.i == ERROR_MALLOC)
		printf("erreur d'allocation de memoire, fonction %s", error.str);
}

void	error_malloc(char *str)
{
	t_pars_error	error;

	error.i = ERROR_MALLOC;
	error.str = str;
	print_error(error);
}
