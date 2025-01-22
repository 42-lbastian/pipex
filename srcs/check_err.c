/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:52:24 by Bastian           #+#    #+#             */
/*   Updated: 2021/11/24 10:56:50 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	ft_check_fd(t_list **lst)
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
