/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:07:11 by Bastian           #+#    #+#             */
/*   Updated: 2021/11/24 11:40:11 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tools.h"
#include "../includes/pipex.h"

void	ft_init_lst(t_list **lst)
{
	(*lst)->cmd = NULL;
	(*lst)->all_path = NULL;
	(*lst)->good_path = NULL;
	(*lst)->fd = NULL;
	(*lst)->fd_in_out = NULL;
	(*lst)->pid = NULL;
}

int	ft_pre_fork(t_list **lst, int argc, char **argv)
{
	ft_init_lst(lst);
	(*lst)->cmd = ft_split_cmd(argv, argc);
	(*lst)->all_path = ft_split(getenv("PATH"), ':');
	if (ft_complete_cmd(lst, argc))
		return (1);
	if (ft_check_malloc(lst))
	{
		free(lst);
		return (3);
	}
	(*lst)->fd_in_out[0] = open(argv[1], O_RDONLY);
	(*lst)->fd_in_out[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (ft_check_fd(lst))
	{
		ft_free_main(lst);
		return (2);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*lst;

	if (argc != 5 || ft_strlen(argv[2]) == 0 || ft_strlen(argv[3]) == 0)
	{
		write(2, "Invalid arg\n", 12);
		return (5);
	}
	lst = malloc(sizeof(t_list));
	if (!lst)
		return (1);
	if (ft_pre_fork(&lst, argc, argv))
	{
		free(lst);
		return (2);
	}
	if (ft_start_fork(&lst, envp))
	{
		ft_free_main(&lst);
		free(lst);
		return (4);
	}
	free(lst);
	return (0);
}
