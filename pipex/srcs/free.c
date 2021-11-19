/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:52:56 by Bastian           #+#    #+#             */
/*   Updated: 2021/11/19 16:14:03 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_cmd(t_list **lst)
{
	int	i;
	int	y;

	y = 0;
	while ((*lst)->cmd[y])
	{
		i = 0;
		while ((*lst)->cmd[y][i])
		{
			free((*lst)->cmd[y][i]);
			i++;
		}
		free((*lst)->cmd[y]);
		y++;
	}
	free((*lst)->cmd);
}

void	ft_free_all_path(t_list **lst)
{
	int	i;

	i = 0;
	while ((*lst)->all_path[i])
	{
		free((*lst)->all_path[i]);
		i++;
	}
	free((*lst)->all_path);
}

void	ft_free_good_path(t_list **lst)
{
	free((*lst)->good_path[0]);
	free((*lst)->good_path[1]);
	free((*lst)->good_path);
}

void	ft_free_main(t_list **lst)
{
	if ((*lst)->cmd)
		ft_free_cmd(lst);
	if ((*lst)->all_path)
		ft_free_all_path(lst);
	if ((*lst)->good_path)
		ft_free_good_path(lst);
	if ((*lst)->pid)
		free((*lst)->pid);
	if ((*lst)->fd)
		free((*lst)->fd);
	if ((*lst)->fd_in_out)
		free((*lst)->fd_in_out);
}
