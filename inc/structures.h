/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:28:59 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/12 19:30:01 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <sys/wait.h>

typedef struct s_lexer
{
	int				id;
	char			*contenu;
	int				type;
	struct s_lexer	*next;
	struct s_lexer	*pre;
}	t_lexer;

typedef struct s_pars_error
{
	int		i;
	char	c;
	char	*str;
}	t_pars_error;

typedef struct s_tab_parse
{
	char	**tab_args;
	char	**infile;
	char	**outfile;
	char	**outredir;
	char	**inredir;
	int		nb_cmd;
	int		nb_redir;
}	t_tab_parse;

typedef struct s_args_exec
{
	char	*path_cmd;
	char	**tab_args;
	char	**tab_env;
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
	int			kill_heredoc;
	int			fd_out_builtin;
	t_tab_parse	*tab_parse;
	pid_t		*childs;
	t_env		*l_env;
	t_args_exec	*args_exec;
}	t_exec_data;

#endif