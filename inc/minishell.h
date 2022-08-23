/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:41:22 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/23 20:28:25 by vbarbier         ###   ########.fr       */
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

typedef struct s_tab_parse
{
	char    **tab_args; //tableau des commandes avec leurs arguments
	char    **infile; //si il y a redirection '<' le nom du fichier d'entree, sinon NULL
	char    **outfile; //si il y a redirection '>' le nom du fichier de sortie, sinon NULL
	char	**outredir;
	char	**inredir;
	int		nb_cmd;
	int		len_char;
}    t_tab_parse;

// utilitaires_parsing.c
char	*chartostr(char c);
int		special_c(char *str);

// lexer.c
void	print_lexer(t_lexer **deb_lexer);
void	lexing(t_lexer **deb_lexer, char *prompt);
void	free_lexer(t_lexer **deb_lexer);
void	create_lexer(t_lexer **deb_lexer, char *str, int type);
void	history(t_lexer **deb_lexer);

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

//parse_to_exec.c
t_tab_parse	*to_exec(t_lexer **deb_lexer);
void		print_to_exec(t_tab_parse *tab_parse);


// error
# define ERROR_MALLOC 42

// test
# define TEST_LEXER 1

#endif