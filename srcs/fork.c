/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:26:33 by Bastian           #+#    #+#             */
/*   Updated: 2021/11/24 10:30:51 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tools.h"
#include "../includes/pipex.h"

void	ft_print_cmd_err(t_list *lst, int i)
{
	write(2, CMD_NOT_FOUND, ft_strlen(CMD_NOT_FOUND));
	write(2, lst->cmd[i][0], ft_strlen(lst->cmd[i][0]));
	write(2, "\n", 1);
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
	return (1);
}

int	ft_start_second_child(t_list **lst, char **envp)
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
	return (0);
}

int	ft_start_fork(t_list **lst, char **envp)
{
	if (pipe((*lst)->fd) == -1)
	{
		perror("Pipe");
		return (1);
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
		if (ft_start_second_child(lst, envp))
			return (1);
	ft_close_all(lst);
	waitpid((*lst)->pid[0], NULL, 0);
	waitpid((*lst)->pid[1], NULL, 0);
	ft_free_main(lst);
	return (0);
}
