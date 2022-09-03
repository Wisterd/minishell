#include "../../inc/minishell.h"

char	*create_temp_file_name()
{
	char	*alpha;
	int		fd;
	char	*file_name;
	int		i;
	int		j;

	alpha = "abcdefghijklmnopqrstuvwxyz";
	fd = -1;
	
	while (fd == -1)
	{
		fd = access(file_name, F_OK);

	}
}