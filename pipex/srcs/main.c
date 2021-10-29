#include "../includes/tools.h"
#include <stdio.h>

char	**ft_complete_cmd(int argc, char ***cmd, char **all_path)
{
	char **good_path;
	int i;
	int y;
	y = 0;
	
	good_path =  malloc(sizeof(char *) * argc - 2);
	if (!(good_path))
		return (NULL);
	while (y < argc - 3)
	{
		i = 0;
		good_path[y] = NULL;
		if (access(cmd[y][0], F_OK | X_OK) == 0)
			good_path[y] = ft_strdup(cmd[y][0]);
		else
		{
			while (all_path[i])
			{
				if (access(ft_strcat_path(all_path[i], cmd[y][0])
						, F_OK | X_OK) == 0)
					good_path[y] = ft_strcat_path(all_path[i], cmd[y][0]);
				i++;
			}
		}
		y++;
	}
	good_path[y] = NULL;
	return (good_path);
}

int	check_cmd(int argc, char **good_path)
{
	int i;

	i = 0;
	while (good_path[i])
		i++;
	if (i == argc - 3)
		return (0);
	return (1);
}

char	***ft_split_cmd(char **argv, int argc)
{
	char ***dst;
	int i;

	i = 0;
	dst = malloc(sizeof(char **) * (argc - 2));
	if (!dst)
		return (NULL);
	while (i < argc - 3)
	{
		dst[i] = ft_split(argv[i + 2], ' ');
		i++;
	}
	dst[i] = 0;
	return (dst);
}

void	ft_print_cmd_err(t_list *main, int i)
{
	write(2, "zsh: command not found: ", ft_strlen("zsh: command not found: "));
	write(2, main->cmd[i][0], ft_strlen(main->cmd[i][0]));
	write(2, "\n", 1);
}

int	ft_first_child(t_list *main)
{
	dup2(main->fd[1], 1);
	dup2(main->fd_in_out[0], 0);
	close(main->fd[0]);
	close(main->fd[1]);
	close(main->fd_in_out[0]);
	close(main->fd_in_out[1]);
	execve(main->good_path[0], main->cmd[0], NULL);
	if (main->good_path[0] == NULL)
		ft_print_cmd_err(main, 0);
	else
		perror(NULL);
	return (0);
}

int	ft_second_child(t_list *main)
{
	dup2(main->fd_in_out[1], 1);
	dup2(main->fd[0], 0);
	close(main->fd[0]);
	close(main->fd[1]);
	close(main->fd_in_out[0]);
	close(main->fd_in_out[1]);
	execve(main->good_path[1], main->cmd[1], NULL);
	if (main->good_path[1] == NULL)
		ft_print_cmd_err(main, 1);
	else
		perror(NULL);
	return (0);
}

int	ft_start_fork(t_list *main)
{
	if (pipe(main->fd) == -1)
	{
		perror("Pipe");
		return(1);
	}
	main->pid[0] = fork();
	if (main->pid[0] == -1)
	{
		perror("Fork");
		return (1);
	}
	else if (main->pid[0] == 0)
		ft_first_child(main);
	else
	{
		main->pid[1] = fork();
		if (main->pid[1] == -1)
		{
			perror("Fork");
			return (2);
		}
		else if (main->pid[1] == 0)
			ft_second_child(main);
	}
	close(main->fd[0]);
	close(main->fd[1]);
	close(main->fd_in_out[0]);
	close(main->fd_in_out[1]);
	waitpid(main->pid[0], NULL, 0);
	waitpid(main->pid[1], NULL, 0);
	return (0);
}

int	ft_check_malloc(t_list **main)
{
	if (!(*main)->good_path)
	{
		perror("Malloc");
		return (1);
	}
	(*main)->pid = malloc(sizeof(int) * 2);
	if (!(*main)->pid)
	{
		perror("Malloc");
		return (3);
	}
	(*main)->fd = malloc(sizeof(int) * 2);
	if (!(*main)->fd)
	{
		perror("Malloc");
		return (4);
	}
	(*main)->fd_in_out = malloc(sizeof(int) * 2);
	if (!(*main)->fd_in_out)
	{
		perror("Malloc");
		return (5);
	}
	return (0);
}

int ft_check_fd(t_list **lst)
{	
	if ((*lst)->fd_in_out[0] == -1)
	{
		return (1);
		perror("open");
	}
	if ((*lst)->fd_in_out[1] == -1)
	{
		return (1);
		perror("open");
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_list	*lst;
	char	**all_path;

	if (argc != 5)
	{
		write(2, "Invalid nb arg\n", 16);
		return (5);
	}
	lst = malloc(sizeof(t_list));
	if (!lst)
	{
		perror("Malloc");
		return (1);
	}
	lst->cmd = ft_split_cmd(argv, argc);
	all_path = ft_split(getenv("PATH"), ':');
	lst->good_path = ft_complete_cmd(argc, lst->cmd, all_path);
	if (ft_check_malloc(&lst))
		return (3);
	lst->fd_in_out[0] = open(argv[1], O_RDONLY);
	lst->fd_in_out[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (!ft_check_fd(&lst))
		return (2);
	if (ft_start_fork(lst))
		return (4);
	return (0);
}
