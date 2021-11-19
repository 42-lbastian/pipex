#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

# define CMD_NOT_FOUND "zsh: command not found: "

typedef struct s_list
{
	char	***cmd;
	char	**all_path;
	char	**good_path;
	int		*fd;
	int		*fd_in_out;
	int		*pid;
}				t_list;

void	ft_free_main(t_list **main);

#endif
