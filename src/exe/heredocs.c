#include "../../inc/minishell.h"

static char	*create_temp_file_name()
{
	int			available;
	char		*file_name;
	long int	num;

	available = 0;
	num = 0;
	file_name = NULL;
	while (available == 0 && num <= INT_MAX)
	{
		file_name = ft_itoa(num);
		available = access(file_name, F_OK);
		num++;
	}
	if (num == INT_MAX && available == 0)
		ft_error(ERR_NO_FILE, "Create temp file", NULL);
	return (file_name);
}

void	write_temp_file(t_exec_data *data, int ind_cmd)
{
	int		fd_here;
	char	*file_name;
	
	file_name = create_temp_file_name();
	fd_here = open(file_name, O_WRONLY);
	if (fd_here == -1)
		ft_error(ERR_PERROR, "Open failed", data->pipes);
	
	ft_free(data->tab_parse[ind_cmd].infile);
	data->tab_parse[ind_cmd].infile = file_name;
}

void	look_for_heredocs(t_exec_data *data)
{
	int	i;

	i = 0;
	while (data->tab_parse)
	{
		i++;
	}
}