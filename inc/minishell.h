/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:41:22 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/28 04:09:13 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define MOT 0
# define CMD 1
# define SPC 2
# define PIPE 3
# define QUOTE 4
# define REDIR 5
# define DOLLAR 6
# define SPECIAL 7

typedef struct s_lexer
{
	int		id;
	char	*contenu;
	int		type;
	struct s_lexer	*next;
	struct s_lexer	*pre;
}			t_lexer;

typedef struct s_pars_error
{
	int	i;
	char c;
	char *fct;
}	t_pars_error;

// lexer.c
void *parse(char *av);

// error
# define ERROR_MALLOC 42
// test
# define TEST_LEXER 1

#endif