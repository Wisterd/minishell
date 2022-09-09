/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:52:44 by vbarbier          #+#    #+#             */
/*   Updated: 2022/09/09 01:54:48 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_to_exec(t_tab_parse *tab_parse)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (tab_parse->nb_cmd > y)
	{
		while (tab_parse->nb_redir > i)
		{
			if (tab_parse[y].infile[i])
				printf("f = %s %d \n", tab_parse[y].infile[i], i);
			if (tab_parse[y].inredir[i])
				printf("r = %s %d \n", tab_parse[y].inredir[i], i);
			if (tab_parse[y].outfile[i])
				printf("f = %s %d \n", tab_parse[y].outfile[i], i);
			if (tab_parse[y].outredir[i])
				printf("r = %s %d \n", tab_parse[y].outredir[i], i);
			i++;
		}
		i = 0;
		y++;
	}
}

t_tab_parse	*fill_tab_inredir(t_tab_parse *tab_parse, \
t_lexer *tmp_lexer, int y, int i)
{
	tab_parse[y].inredir[i] = ft_strdup(tmp_lexer->contenu);
	error_malloc("exec inredir", tab_parse[y].inredir[i]);
	tab_parse[y].infile[i] = ft_strdup(tmp_lexer->next->contenu);
	error_malloc("exec inrdile", tab_parse[y].infile[i]);
	return (tab_parse);
}

t_tab_parse *exec_redir(t_lexer *tmp_lexer, t_tab_parse *tab_parse, int y, int x)
{
    static int    cpy = 0;
    static int    i = 0;
    static int    z = 0;

    if (cpy != y || (x == 0 && y == 0))
    {
        i = 0;
        z = 0;
    }
    if (tmp_lexer->type == REDIR)
    {
        if (!ft_strncmp(tmp_lexer->contenu, "<<", 2) || \
        !ft_strncmp(tmp_lexer->contenu, "<", 1))
            tab_parse = fill_tab_inredir(tab_parse, tmp_lexer, y, i++);
        else
        {
            tab_parse[y].outredir[z] = ft_strdup(tmp_lexer->contenu);
            error_malloc("exec outredir", tab_parse[y].outredir[z]);
            tab_parse[y].outfile[z] = ft_strdup(tmp_lexer->next->contenu);
            error_malloc("exec outfile", tab_parse[y].outfile[z]);
            z++;
        }
    }
    cpy = y;
    return (tab_parse);
}

int    conditon(t_lexer *tmp_lexer)
{
    return ((tmp_lexer->type == MOT || tmp_lexer->type == DOLLAR)\
    && (!tmp_lexer->pre || \
    (tmp_lexer->pre && tmp_lexer->pre->type != REDIR)));
}

t_tab_parse    *to_exec(t_lexer **deb_lexer)
{
    int            i;
    int            y;
    int             x;
    t_lexer        *tmp_lexer;
    t_tab_parse    *tab_parse;

    tmp_lexer = *deb_lexer;
    i = 0;
    y = 0;
    x = 0;
    tab_parse = init_tab_parse(deb_lexer);
    while (tmp_lexer)
    {
        tab_parse = exec_redir(tmp_lexer, tab_parse, y, x++);
        if (conditon(tmp_lexer))
        {
            tab_parse[y].tab_args[i] = ft_strdup(tmp_lexer->contenu);
            error_malloc("to_exec", tab_parse[y].tab_args[i++]);
        }
        if (tmp_lexer->type == PIPE)
        {
            y++;
            i = 0;
        }
        tmp_lexer = tmp_lexer->next;
    }
    return (tab_parse);
}
