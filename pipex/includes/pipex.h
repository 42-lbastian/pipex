#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_list
{
	char	***cmd;
	char	**good_path;
	int		*fd;
	int		*fd_in_out;
	int		*pid;
}				t_list;

#endif
