/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:59:48 by Bastian           #+#    #+#             */
/*   Updated: 2021/11/24 14:59:56 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

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

void	ft_free_main(t_list **lst);
void	ft_close_all(t_list **lst);
int		ft_start_fork(t_list **lst, char **envp);
int		ft_check_malloc(t_list **lst);
int		ft_check_fd(t_list **lst);
char	***ft_split_cmd(char **argv, int argc);
int		ft_complete_cmd(t_list **lst, int argc);

#endif
