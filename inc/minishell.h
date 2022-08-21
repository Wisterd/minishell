/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:41:22 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/20 22:04:10 by vbarbier         ###   ########.fr       */
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
# define REDIR2 6
# define DOLLAR 7
# define SPECIAL 8

typedef struct s_lexer
{
	int				id;
	char			*contenu;
	int				type;
	struct s_lexer	*next;
	struct s_lexer	*pre;
}			t_lexer;

typedef struct s_pars_error
{
	int		i;
	char	c;
	char	*str;
}	t_pars_error;

typedef struct s_tab
{
    char            **tab;
    struct s_tab    *next;
    struct s_tab    *prev;
}    t_tab;

typedef struct s_args_exec
{
    char    **path_cmds;
    t_tab    *tab_args;
    char     **path;
}    t_args_exec;

// utilitaires_parsing.c
char	*chartostr(char c);
int		special_c(char *str);

// lexer.c
void	print_lexer(t_lexer **deb_lexer);
void	lexing(t_lexer **deb_lexer, char *prompt);
void	free_lexer(t_lexer **deb_lexer);
void	create_lexer(t_lexer **deb_lexer, char *str, int type);

//lexer2.c
void	fuz_lex(t_lexer **deb_lexer, int type);
void	word_or_cmd(t_lexer **deb_lexer);
void	free_one_element(t_lexer **deb_lexer, t_lexer *tmp_lexer);

//valide_lexer.c
int		valide_lexer(t_lexer **deb_lexer);

// error.c
void	print_error(t_pars_error error);
void	error_malloc(char *str);

int		in_quote(t_lexer **deb_lexer);


// error
# define ERROR_MALLOC 42

// test
# define TEST_LEXER 1

#endif