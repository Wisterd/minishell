/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tab_to_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:19:00 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/08 18:24:10 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**init_arg_cmd(t_lexer **deb_lexer, t_tab_parse *tab_parse)
{
	int			i;
	int			y;
	t_lexer		*tmp_lexer;

	tmp_lexer = *deb_lexer;
	y = 0;
	i = 0;
	while (tmp_lexer)
	{
		if ((tmp_lexer->type == MOT || tmp_lexer->type == DOLLAR)
		&& (!tmp_lexer->pre || (tmp_lexer->pre && tmp_lexer->pre->type != REDIR)))
			i++;
		if (tmp_lexer->type == PIPE || !tmp_lexer->next)
		{
			tab_parse[y].tab_args = ft_malloc(sizeof(char **) * (i + 1));
			error_malloc("init_arg_cmd", tab_parse[y].tab_args);
			while (i > -1)
				tab_parse[y].tab_args[i--] = NULL;
			y++;
			i = 0;
		}
		tmp_lexer = tmp_lexer->next;
	}
	return (tab_parse->tab_args);
}

int	lex_nb_redir(t_lexer **deb_lexer)
{
	int			i;
	t_lexer		*tmp_lexer;

	i = 0;
	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		if (tmp_lexer->type == REDIR)
			i++;
		tmp_lexer = tmp_lexer->next;
	}
	return (i);
}

t_tab_parse	*init_tab_chars(t_lexer **deb_lexer, t_tab_parse *tab_parse)
{
	int	y;

	tab_parse->nb_redir = lex_nb_redir(deb_lexer) + 1;
	y = 0;
	tab_parse[y].tab_args = init_arg_cmd(deb_lexer, tab_parse);
	while (tab_parse->nb_cmd > y)
	{
		tab_parse[y].infile = ft_malloc(sizeof(char **) * tab_parse->nb_redir);
		error_malloc("init_tab_infile", tab_parse[y].infile);
		tab_parse[y].outfile = ft_malloc(sizeof(char **) * tab_parse->nb_redir);
		error_malloc("init_tab_outfile", tab_parse[y].outfile);
		tab_parse[y].inredir = ft_malloc(sizeof(char **) * tab_parse->nb_redir);
		error_malloc("init_tab_inredir", tab_parse[y].inredir);
		tab_parse[y].outredir = ft_malloc(\
		sizeof(char **) * tab_parse->nb_redir);
		error_malloc("init_tab_outredir", tab_parse[y].outredir);
		y++;
	}
	return (tab_parse);
}

t_tab_parse	*init_tab_null(t_tab_parse *tab_parse)
{
	int			i;
	int			y;

	i = 0;
	y = 0;
	while (tab_parse->nb_cmd > y)
	{
		i = 0;
		while (i < tab_parse->nb_redir)
		{
			tab_parse[y].infile[i] = NULL;
			tab_parse[y].outfile[i] = NULL;
			tab_parse[y].inredir[i] = NULL;
			tab_parse[y].outredir[i] = NULL;
			i++;
		}
		i = 0;
		y++;
	}
	i = 0;
	return (tab_parse);
}

t_tab_parse	*init_tab_parse(t_lexer **deb_lexer)
{
	int			i;
	t_tab_parse	*tab_parse;
	t_lexer		*tmp_lexer;

	tmp_lexer = *deb_lexer;
	i = 1;
	while (tmp_lexer)
	{
		if (tmp_lexer->type == PIPE)
			i++;
		tmp_lexer = tmp_lexer->next;
	}
	tab_parse = ft_malloc(sizeof(t_tab_parse) * i);
	error_malloc("init_tab_parse", tab_parse);
	tab_parse->nb_cmd = i;
	tab_parse = init_tab_chars(deb_lexer, tab_parse);
	tab_parse = init_tab_null(tab_parse);
	return (tab_parse);
}
