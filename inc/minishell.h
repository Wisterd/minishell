/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvue <mvue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:41:22 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/08 22:58:33 by mvue             ###   ########.fr       */
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
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include "../libft/libft.h"
# include "structures.h"

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
# define ERR_DIR 17

extern int g_exit_stat;

//EXE
//error.c
void		ft_error(int error_code, char *to_print, t_exec_data *data);

//path.c
char		*get_path_cmd(t_exec_data *data, char *cmd);

//utils.c
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_wait(t_exec_data *data);
void		ft_exit_error(int exit_stat);
char		*ft_getcwd();
char		*ft_getcwd_perm();

//pipe.c
void		ft_exec(t_args_exec args_exec);
void		ft_close_pipes(t_exec_data *data);
int			ft_fork(t_exec_data *data);
void		fill_pipes(t_exec_data *data);
//childs.c 
void		ft_child(t_exec_data *data);

//init.c
void		init_data(t_exec_data *data);
int			*init_pipes(t_exec_data *data);

//one_cmd.c
int			exe_one_cmd(t_exec_data *data);

//redirs.c
int			get_ind_last_redir(char **redirs);
void		create_all_out(t_exec_data *data, char **outfiles);
void		open_all_in(t_exec_data *data, char **infiles);
void		unlink_heredocs(t_exec_data *data);

//heredocs.c
void		look_for_heredocs(t_exec_data *data);

///BUILTINS
//exe_builtins.c
void		exe_builtin(t_exec_data *data);
int			is_builtin(char *cmd);
//env.c
t_env		*init_env(char **envp);
void		ft_env(t_exec_data *data);
char		*ft_getenv(char *to_get, t_exec_data *data);
char		**ft_get_total_env(t_exec_data *data);
//unset.c
void		ft_unset(t_exec_data *data);

//export.c
void		ft_export(t_exec_data *data);

//export2.c
int			search_replace_var_name(t_env *l_env, char *var_name, char *var_content);

//echo.c
void		ft_echo(t_exec_data *data);

//exit.c
void	ft_exit(t_exec_data *data);

//cd.c
void	ft_cd(t_exec_data	*data);

//pwd.c
int	ft_pwd(t_exec_data *data);

//cd.c
void	ft_cd(t_exec_data *data);

//utils_env.c
void		l_add_back(t_env **l_env, char *var_name, \
	char *var_content);
char		*get_var_content(char *var_path);
char		*get_var_name(char *var_path);
int			protected_putstr(char *str, char *builtin, t_exec_data *data);

// utilitaires_parsing.c
char	*chartostr(char c);
int		special_c(char *str);

// lexer.c
void	print_lexer(t_lexer **deb_lexer);
void	free_lexer(t_lexer **deb_lexer);
void	create_lexer(t_lexer **deb_lexer, char *str, int type);
void	history(t_lexer **deb_lexer);
void	lexing(t_lexer **deb_lexer, char *prompt);

//lexer2.c
t_lexer	**create_deb_lexer(void);
void	fuz_lex(t_lexer **deb_lexer, int type);
void	fuz_lex1(t_lexer **deb_lexer, int type);
void	free_one_element(t_lexer **deb_lexer, t_lexer *tmp_lexer);
int		len_lexer(t_lexer **deb_lexer);

// fuz_and_remove_lexer.c
int		near_mot(t_lexer **deb_lexer);
int		in_quote(t_lexer **deb_lexer);
int		have_type(t_lexer **deb_lexer, int type);
void	remove_type(t_lexer **deb_lexer, int type);

//valide_lexer.c
int		valide_lexer(t_lexer **deb_lexer, t_exec_data *data);

//valide_lexer_dollar.c
t_lexer	*replace_dollar(t_lexer **deb_lexer, t_lexer *tmp_lexer, t_exec_data *data);

// error.c
void	print_error(t_pars_error error);
void	error_malloc(char *str, void *not_null);

int		in_quote(t_lexer **deb_lexer);

//	init_tab_to_exec.c
t_tab_parse	*init_tab_parse(t_lexer **deb_lexer);

// parse_to_exec.c
t_tab_parse	*to_exec(t_lexer **deb_lexer);
void		print_to_exec(t_tab_parse *tab_parse);

// signal.c
void		signals();
void		signal_heredoc(void);

// parsing.c
void	mini_exit(char *prompt, t_exec_data *data);

// error
# define ERROR_MALLOC 42

// test
# define TEST_LEXER 1

#endif