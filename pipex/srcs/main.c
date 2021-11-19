#include "../includes/tools.h"
#include <stdio.h>

int	ft_is_relative(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ft_complete_cmd(t_list **lst, int argc, char ***cmd, char **all_path)
{
	int i;
	int y;
	y = 0;
	
	(*lst)->good_path =  malloc(sizeof(char *) * (argc - 2));
	if (!((*lst)->good_path))
	{
		perror("malloc");
		return (1);
	}
	while (y < argc - 3)
	{
		i = 0;
		(*lst)->good_path[y] = NULL;
		if (ft_is_relative(cmd[y][0]))
			(*lst)->good_path[y] = ft_strdup(cmd[y][0]);
		else
		{
			while (all_path[i])
			{
				(*lst)->good_path[y] = ft_strcat_path(all_path[i], cmd[y][0]);
				if (access((*lst)->good_path[y],F_OK ) == 0)
					break;
				else
				{
					free((*lst)->good_path[y]);
					(*lst)->good_path[y] = NULL;
				}
				i++;
			}
		}
		y++;
	}
	(*lst)->good_path[y] = NULL;
	return (0);
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

void	ft_print_cmd_err(t_list *lst, int i)
{
	write(2, CMD_NOT_FOUND, ft_strlen(CMD_NOT_FOUND));
	write(2, lst->cmd[i][0], ft_strlen(lst->cmd[i][0]));
	write(2, "\n", 1);
}

void	ft_close_all(t_list **lst)
{
	close((*lst)->fd[0]);
	close((*lst)->fd[1]);	
	close((*lst)->fd_in_out[0]);
	close((*lst)->fd_in_out[1]);
}

int	ft_first_child(t_list **lst, char **envp)
{
	dup2((*lst)->fd[1], 1);
	dup2((*lst)->fd_in_out[0], 0);
	ft_close_all(&(*lst));
	execve((*lst)->good_path[0], (*lst)->cmd[0], envp);
	if ((*lst)->good_path[0] == NULL)
		ft_print_cmd_err((*lst), 0);
	else
		perror(NULL);
	ft_free_main(lst);
	return (1);
}

int	ft_second_child(t_list **lst, char **envp)
{
	dup2((*lst)->fd_in_out[1], 1);
	dup2((*lst)->fd[0], 0);
	ft_close_all(&(*lst));
	execve((*lst)->good_path[1], (*lst)->cmd[1], envp);
	if ((*lst)->good_path[1] == NULL)
		ft_print_cmd_err((*lst), 1);
	else
		perror(NULL);
	ft_free_main(lst);
	return (1);
}

int	ft_start_fork(t_list **lst, char **envp)
{
	if (pipe((*lst)->fd) == -1)
	{
		perror("Pipe");
		return(1);
	}
	(*lst)->pid[0] = fork();
	if ((*lst)->pid[0] == -1)
	{
		perror("Fork");
		return (1);
	}
	else if ((*lst)->pid[0] == 0)
	{
		if (ft_first_child(lst, envp))
			return (1);
	}
	else
	{
		(*lst)->pid[1] = fork();
		if ((*lst)->pid[1] == -1)
		{
			perror("Fork");
			return (2);
		}
		else if ((*lst)->pid[1] == 0)
		{
			if (ft_second_child(lst, envp))
				return (1);
		}
	}
	ft_close_all(lst);
	waitpid((*lst)->pid[0], NULL, 0);
	waitpid((*lst)->pid[1], NULL, 0);
	ft_free_main(lst);
	return (0);
}

int	ft_check_malloc(t_list **lst)
{
	(*lst)->pid = malloc(sizeof(int) * 2);
	(*lst)->fd = malloc(sizeof(int) * 2);
	(*lst)->fd_in_out = malloc(sizeof(int) * 2);
	if (!(*lst)->pid || !(*lst)->fd || !(*lst)->fd_in_out)
	{
		ft_free_main(lst);
		perror("Malloc");
		return (1);
	}
	return (0);
}

int ft_check_fd(t_list **lst)
{	
	if ((*lst)->fd_in_out[0] == -1)
	{
		perror("open");
		return (1);
	}
	if ((*lst)->fd_in_out[1] == -1)
	{
		perror("open");
		return (1);
	}
	return (0);
}

void	ft_init_lst(t_list **lst)
{
	(*lst)->cmd = NULL;
	(*lst)->all_path = NULL;
	(*lst)->good_path = NULL;
	(*lst)->fd = NULL;
	(*lst)->fd_in_out = NULL;
	(*lst)->pid = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_list	*lst;

	if (argc != 5 || ft_strlen(argv[2]) == 0 || ft_strlen(argv[3]) == 0)
	{
		write(2, "Invalid arg\n", 12);
		return (5);
	}
	lst = malloc(sizeof(t_list));
	if (!lst)
	{
		perror("Malloc");
		return (1);
	}
	ft_init_lst(&lst);
	lst->cmd = ft_split_cmd(argv, argc);
	lst->all_path = ft_split(getenv("PATH"), ':');
	if (ft_complete_cmd(&lst, argc, lst->cmd, lst->all_path))
		return (1);
	if (ft_check_malloc(&lst))
	{
		free(lst);
		return (3);
	}
	lst->fd_in_out[0] = open(argv[1], O_RDONLY);
	lst->fd_in_out[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (ft_check_fd(&lst))
	{
		ft_free_main(&lst);
		free(lst);
		return (2);
	}
	if (ft_start_fork(&lst, envp))
	{
		free(lst);
		return (4);
	}
	free(lst);
	return (0);
}
