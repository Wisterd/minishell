#include "../../inc/minishell.h"

t_args_exec	*init_args_exec(void)
{
	t_args_exec	*args_exec;
	char		**path;
	char		**cmd1;
	char		**cmd2;
	char		**cmd3;
	char		**cmd4;
	char		***tab_args;

	args_exec = ft_malloc(sizeof(t_args_exec));
	tab_args = ft_malloc(sizeof(char **) * 4);
	cmd1 = ft_malloc(sizeof(char *) * 3);
	cmd2 = ft_malloc(sizeof(char *) * 3);
	cmd3 = ft_malloc(sizeof(char *) * 3);
	cmd4 = ft_malloc(sizeof(char *) * 3);
	cmd1[0] = ft_strdup("cat");
	cmd1[1] = ft_strdup("in0");
	cmd1[2] = NULL;
	cmd2[0] = ft_strdup("cat");
	cmd2[1] = ft_strdup("in1");
	cmd2[2] = NULL;
	cmd3[0] = ft_strdup("wc");
	cmd3[1] = ft_strdup("-l");
	cmd3[2] = NULL;
	cmd4[0] = ft_strdup("cat");
	cmd4[1] = ft_strdup("in2");
	cmd4[2] = NULL;
	tab_args[0] = cmd1;
	tab_args[1] = cmd2;
	tab_args[2] = cmd3;
	tab_args[3] = cmd4;
	args_exec->tab_args = tab_args;
	path = ft_split(getenv("PATH"), ':');
	args_exec->path = path;
	return (args_exec);
}

void	set_inoutfies(t_exec_data *data)
{
	char	**infiles;
	char	**outfiles;

	infiles = ft_malloc(sizeof(char *) * 4);
	outfiles = ft_malloc(sizeof(char *) * 4);
	/*
	infiles[0] = "in0";
	infiles[1] = "in1";
	infiles[2] = "in2";
	infiles[3] = "in3";
	outfiles[0] = NULL;
	outfiles[1] = NULL;
	outfiles[2] = NULL;
	outfiles[3] = NULL;
	*/
	infiles[0] = NULL;
	infiles[1] = NULL;
	infiles[2] = NULL;
	infiles[3] = NULL;
	outfiles[0] = NULL;
	outfiles[1] = NULL;
	outfiles[2] = NULL;
	outfiles[3] = NULL;
	data->infile = infiles;
	data->outfile = outfiles;
}

void	set_redirs(t_exec_data	*data)
{
	char	**redir_in;
	char	**redir_out;

	redir_in = ft_malloc(sizeof(char *) * 4);
	redir_out = ft_malloc(sizeof(char *) * 4);
	redir_in[0] = "<";
	redir_in[1] = "<";
	redir_in[2] = "<";
	redir_in[3] = "<";
	redir_out[0] = ">>";
	redir_out[1] = ">";
	redir_out[2] = ">";
	redir_out[3] = ">";
	data->redir_in = redir_in;
	data->redir_out = redir_out;
}