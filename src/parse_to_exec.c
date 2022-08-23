/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:52:44 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/23 21:06:15 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_to_exec(t_tab_parse *tab_parse)
{
	int i;
	int y;

	i = 1;
	y = 1;
	while (tab_parse->nb_cmd > y)
	{
		while (tab_parse->len_char > i)
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

t_tab_parse *init_tab_parse(t_lexer **deb_lexer)
{
	int			i;
	int			y;
	t_tab_parse *tab_parse;
	t_lexer		*tmp_lexer;
	// MALLOC de nb cmd donc tab struct
	tmp_lexer = *deb_lexer;
	i = 1;
	y = 0;
	while (tmp_lexer)
	{
		if (tmp_lexer->type  == PIPE)
			i++;
		tmp_lexer = tmp_lexer->next;
	}
	tab_parse = malloc(sizeof(t_tab_parse) * i);
	// while (y < i)
	// {
	 	tab_parse->nb_cmd = i;
		printf("LA = %d   \n", tab_parse->nb_cmd );
		
	// }
	y = 0;
	i = 1;
	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		if (tmp_lexer->type == REDIR)
			i++;
		tmp_lexer = tmp_lexer->next;
	}
	while (y < tab_parse->nb_cmd)
	{
		tab_parse->len_char = i;
		y++;
	}
	y = 0;
		// MALLOC des str au bonne indices du tab struc
	while (tab_parse->nb_cmd > y)
	{
		tab_parse[y].infile = malloc(sizeof(char **) * i);
		tab_parse[y].outfile = malloc(sizeof(char **) * i);
		tab_parse[y].inredir = malloc(sizeof(char **) * i);
		tab_parse[y].outredir = malloc(sizeof(char **) * i);
		y++;
	}
	while (i)
	{
		tab_parse->infile = malloc(sizeof(char *) * i);
		tab_parse->outfile = malloc(sizeof(char *) * i);
		tab_parse->inredir = malloc(sizeof(char *) * i);
		tab_parse->outredir = malloc(sizeof(char *) * i);
		i--;
	}
	i = 0;
	y = 0;
	while (tab_parse->nb_cmd > y + 1)
	{
		while (i + 1 < tab_parse->len_char)
		{
			printf("i=%d   y=%d \n", i,y);
			tab_parse[y].infile[i] = NULL;
			tab_parse[y].outfile[i] = NULL;
			tab_parse[y].inredir[i] = NULL;
			tab_parse[y].outredir[i] = NULL;
			i++;
		}
		y++;
	}
	i = 0;
	// while (tmp_lexer)
	// {
	// 	if (tmp_lexer->type == MOT && tmp_lexer.pre && !tmp_lexer->pre->type == REDIR)
	// 		i++;
	// 	tmp_lexer = tmp_lexer->next;
	// }
	// tab_parse->outredir = malloc(sizeof(char **) * i);
	return (tab_parse);
}

t_tab_parse	*to_exec(t_lexer **deb_lexer)
{
	int			i;
	int			y;
	t_lexer		*tmp_lexer;
	t_tab_parse	*tab_parse;

	tmp_lexer = *deb_lexer;
	i = 0;
	y = 0;
	tab_parse = init_tab_parse(deb_lexer);
	// tab_parse = init_tab_parse(deb_lexer);
	// tab_parse->tab_args = init_tab_args(deb_lexer);
	while (tmp_lexer)
	{
		if (tmp_lexer->type == REDIR)
		{
			if (!ft_strncmp(tmp_lexer->contenu, "<<", 2) || \
			!ft_strncmp(tmp_lexer->contenu, "<", 1))
			{
				tab_parse[i].inredir[y] = ft_strdup(tmp_lexer->contenu);
				tab_parse[i].infile[y] = ft_strdup(tmp_lexer->next->contenu);
				// printf("bla = %s ok", tab_parse->inredir[i]);
				// printf("bla = %s  i = %d ok", tab_parse->infile[i], i);
			}
			else
			{
				tab_parse[i].outredir[y] = ft_strdup(tmp_lexer->contenu);
				// printf("bla = %s ok", tab_parse->outredir[i]);
				tab_parse[i].outfile[y] = ft_strdup(tmp_lexer->next->contenu);				
			}
			i++;
			tmp_lexer = tmp_lexer->next;
		}
		else
		{
			if (tmp_lexer && tmp_lexer->type != REDIR)
			{
				if (tmp_lexer->type == PIPE)
				{
					y++;
					tmp_lexer = tmp_lexer->next;
				}
			}
		}
		tmp_lexer = tmp_lexer->next;
	}
	return(tab_parse);
}
