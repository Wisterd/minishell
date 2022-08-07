/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 23:58:48 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/08 00:04:52 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_error(t_pars_error error)
{
	if (error.i == SPECIAL)
		printf("erreur de syntaxe près du symbole inattendu « %c »\n", error.c);
	if (error.i == ERROR_MALLOC)
		printf("erreur d'allocation de memoire, fonction %s", error.fct);
}

void	error_malloc(char *str)
{
	t_pars_error	error;
	error.i = ERROR_MALLOC;
	error.fct = str;
	print_error(error);
}
