/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:52:44 by vbarbier          #+#    #+#             */
/*   Updated: 2022/08/29 20:46:20 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void	print_to_exec(t_tab_parse *tab_parse)
{
	int i;
	int y;

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
		// printf("i =%d  Y = %d\n", i, y);
		if (tmp_lexer->type == MOT && (!tmp_lexer->pre || (tmp_lexer->pre && tmp_lexer->pre->type != REDIR)))
			i++;
		if (tmp_lexer->type == PIPE || !tmp_lexer->next)
		{
			tab_parse[y].tab_args = ft_malloc(sizeof(char **) * (i + 1));
			error_malloc("init_arg_cmd", tab_parse[y].tab_args);
			while (i > -1)
			{
				tab_parse[y].tab_args[i] = NULL;
				// printf("----------%p, i =%d  Y = %d\n", tab_parse[y].tab_args[i], i, y);
				i--;
			}
			y++;
			i = 0;
		}
		tmp_lexer = tmp_lexer->next;
	}
	return (tab_parse->tab_args);
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
	tab_parse = ft_malloc(sizeof(t_tab_parse) * i);
	error_malloc("init_tab_parse", tab_parse);
	tab_parse->nb_cmd = i;
	//printf("nb cmd = %d \n", tab_parse->nb_cmd);
		


	i = 0;
	y = 0;
	tmp_lexer = *deb_lexer;
	while (tmp_lexer)
	{
		if (tmp_lexer->type == REDIR)
			i++;
		tmp_lexer = tmp_lexer->next;
	}
	tab_parse->nb_redir = i + 1;
	//printf("lenCHAR = %d \n", tab_parse->nb_redir);
	y = 0;
		// MALLOC des str au bonne indices du tab struc
	tab_parse[y].tab_args = init_arg_cmd(deb_lexer, tab_parse);
	while (tab_parse->nb_cmd > y)
	{
		tab_parse[y].infile = ft_malloc(sizeof(char **) * tab_parse->nb_redir);
		error_malloc("init_tab_infile", tab_parse[y].infile );
		tab_parse[y].outfile = ft_malloc(sizeof(char **) * tab_parse->nb_redir);
		error_malloc("init_tab_outfile", tab_parse[y].outfile);
		tab_parse[y].inredir = ft_malloc(sizeof(char **) * tab_parse->nb_redir);
		error_malloc("init_tab_inredir", tab_parse[y].inredir);
		tab_parse[y].outredir = ft_malloc(sizeof(char **) * tab_parse->nb_redir);
		error_malloc("init_tab_outredir", tab_parse[y].outredir);
		y++;
	}
	// printf("nb arg cmd = %d\n", nb_arg_cmd(deb_lexer));
	// printf("nb_cmd = %d\n", tab_parse->nb_cmd);

	i = 0;
	y = 0;
	// while (tab_parse->nb_cmd > y)
	// {
	// 	while (i < len_lexer(deb_lexer))
	// 	{
	// 		tab_parse[y].tab_args[i] =ft_malloc(sizeof(char *) * len_lexer(deb_lexer) + 1);
	// 		i++;
	// 	}
	// 	i = 0;	
	// 	while (i < tab_parse->nb_redir)
	// 	{
	// 		//printf("la===%d", len_lexer(deb_lexer));
	// 		tab_parse[y].infile[i] = malloc(sizeof(char *) * tab_parse->nb_redir);
	// 		tab_parse[y].outfile[i] = malloc(sizeof(char *) * tab_parse->nb_redir);
	// 		tab_parse[y].inredir[i] = malloc(sizeof(char *) * tab_parse->nb_redir);
	// 		tab_parse[y].outredir[i] = malloc(sizeof(char *) * tab_parse->nb_redir);
	// 		i++;
	// 	}
	// 	i = 0;
	// 	y++;
	// }


	i = 0;
	y = 0;
	while (tab_parse->nb_cmd > y)
	{
		// printf("----------- Y =%d\n", y);
		// while (i < nb_arg_cmd(deb_lexer) + 1)
		// {
		// 	tab_parse[y].tab_args[i] = NULL;
		// 	printf("----------%p, i =%d\n", tab_parse[y].tab_args[i], i);
		// 	i++;
		// }
		i = 0;
		while (i < tab_parse->nb_redir)
		{
			// printf(" LA ---------------i=%d   y=%d \n", i,y);
			
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

t_tab_parse	*exec_redir(t_lexer *tmp_lexer, t_tab_parse	*tab_parse, int y)
{
	static int	cpy = 0;
	static int	i = 0;
	static int	z = 0;

	if (cpy != y)
	{
		i = 0;
		z = 0;
	}
	if (tmp_lexer->type == REDIR)
	{
		if (!ft_strncmp(tmp_lexer->contenu, "<<", 2) || \
		!ft_strncmp(tmp_lexer->contenu, "<", 1))
		{
			tab_parse[y].inredir[i] = ft_strdup(tmp_lexer->contenu);
			error_malloc("exec inredir", tab_parse[y].inredir[i]);
			tab_parse[y].infile[i] = ft_strdup(tmp_lexer->next->contenu);
			error_malloc("exec inrdile", tab_parse[y].infile[i]);
			// printf("bla = %s  y = %d i = %d \n", tab_parse[y].infile[i], y, i);
			i++;
		}
		else
		{
			tab_parse[y].outredir[z] = ft_strdup(tmp_lexer->contenu);
			error_malloc("exec outredir", tab_parse[y].outredir[z]);
			tab_parse[y].outfile[z] = ft_strdup(tmp_lexer->next->contenu);
			error_malloc("exec outfile", tab_parse[y].outfile[z]);
			// printf("bla = %s  y = %d i = %d \n", tab_parse[y].outfile[z], y, z);		
			z++;
		}
	}
	cpy = y;
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
	while (tmp_lexer)
	{
		tab_parse = exec_redir(tmp_lexer, tab_parse, y);
		if (tmp_lexer->type == MOT && (!tmp_lexer->pre || (tmp_lexer->pre && tmp_lexer->pre->type != REDIR)))
		{
			tab_parse[y].tab_args[i] = ft_strdup(tmp_lexer->contenu);
			error_malloc("to_exec", tab_parse[y].tab_args[i]);
			// printf("args = %s  y = %d i = %d \n",tab_parse[y].tab_args[i], y, i);
			i++;
		}
		if (tmp_lexer->type == PIPE)
		{
			y++;
			i = 0;
		}
		tmp_lexer = tmp_lexer->next;
	}
	return(tab_parse);
}
