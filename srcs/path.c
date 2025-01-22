/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:39:16 by Bastian           #+#    #+#             */
/*   Updated: 2021/11/24 11:39:53 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tools.h"
#include "../includes/pipex.h"

void	ft_found_path(t_list **lst, int y, int i)
{
	while ((*lst)->all_path[i])
	{
		(*lst)->good_path[y] = ft_strcat_path((*lst)->all_path[i],
				(*lst)->cmd[y][0], 0);
		if (access((*lst)->good_path[y], F_OK) == 0)
			break ;
		else
		{
			free((*lst)->good_path[y]);
			(*lst)->good_path[y] = NULL;
		}
		i++;
	}
}

int	ft_complete_cmd(t_list **lst, int argc)
{
	int	y;

	y = 0;
	(*lst)->good_path = malloc(sizeof(char *) * (argc - 2));
	if (!((*lst)->good_path))
	{
		perror("malloc");
		return (1);
	}
	while (y < argc - 3)
	{
		(*lst)->good_path[y] = NULL;
		if (ft_is_relative((*lst)->cmd[y][0]))
			(*lst)->good_path[y] = ft_strdup((*lst)->cmd[y][0]);
		else
			ft_found_path(lst, y, 0);
		y++;
	}
	(*lst)->good_path[y] = NULL;
	return (0);
}

char	***ft_split_cmd(char **argv, int argc)
{
	char	***dst;
	int		i;

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
