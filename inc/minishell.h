/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:41:22 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/26 19:01:03 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
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
# define EXISTS 10
# define ACCESSIBLE 11
# define ERR_MALLOC 12
# define ERR_NOT_FOUND 13
# define ERR_NO_FILE 14
# define ERR_PERM_DENIED 15
# define ERR_PERROR 16

extern int g_exit_stat;

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
	int		nb_redir;
}    t_tab_parse;

typedef struct s_args_exec
{
	char	*path_cmd;
	char	***tab_args;
	char 	**path;
}	t_args_exec;

typedef struct s_env
{
	struct s_env	*prev;
	struct s_env	*next;
	char			*var_name;
	char			*var_content;
}	t_env;

typedef struct s_exec_data
{
	int			n_cmds;
	int			ind_cmd;
	int			*pipes;
	int			*l_pipe;
	int			*r_pipe;
	t_tab_parse	*tab_parse;
	pid_t		*childs;
	t_env		*l_env;
	t_args_exec *args_exec;
}	t_exec_data;

//EXE
//error.c
void		ft_error(int error_code, char *to_print, int *pipes);

//path.c
char		*get_path_cmd(t_exec_data *data, char *cmd);

//utils.c
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_wait(t_exec_data *data);
void		ft_exit(void);
char		*ft_getcwd(t_exec_data *data);

//pipe.c
void		ft_exec(t_args_exec args_exec, int ind_cmd, int *pipes);
void		ft_close_pipes(int	*pipes, int dont_close);
int			*init_pipes(t_exec_data *data);
void		init_data(t_exec_data *data);

//childs.c 
void		ft_child(t_exec_data *exec_data, int ind_cmd);

//init.c
t_args_exec	*init_args_exec(void);
void		set_inoutfies(t_exec_data *data);
void		set_redirs(t_exec_data	*data);

//BUILTINS
//env.c
t_env		*init_env(t_exec_data *data, char **envp);
void		ft_env(t_exec_data *data);

//unset.c
void	ft_unset(t_exec_data *data, char *var_name);


//paring.c
void	mini_exit(char *prompt, t_exec_data *data);

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
//void	word_or_cmd(t_lexer **deb_lexer);
void	free_one_element(t_lexer **deb_lexer, t_lexer *tmp_lexer);
int		len_lexer(t_lexer **deb_lexer);
//valide_lexer.c
int		valide_lexer(t_lexer **deb_lexer);

// error.c
void	print_error(t_pars_error error);
void	error_malloc(char *str);

int		in_quote(t_lexer **deb_lexer);

//parse_to_exec.c
t_tab_parse	*to_exec(t_lexer **deb_lexer);
void		print_to_exec(t_tab_parse *tab_parse);

//signal.c
void		signals();
// error
# define ERROR_MALLOC 42

// test
# define TEST_LEXER 1

#endif