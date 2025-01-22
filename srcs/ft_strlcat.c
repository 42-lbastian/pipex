/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:39:21 by lbastian          #+#    #+#             */
/*   Updated: 2021/11/24 11:03:07 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tools.h"

char	*ft_strcat_path(char *str1, char *str2, int y)
{
	char	*dst;
	int		i;

	i = 0;
	y = 0;
	dst = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 2));
	if (!dst)
		return (NULL);
	while (str1[i])
	{
		dst[y] = str1[i];
		y++;
		i++;
	}
	dst[y] = '/';
	y++;
	i = 0;
	while (str2[i])
	{
		dst[y] = str2[i];
		y++;
		i++;
	}
	dst[y] = 0;
	return (dst);
}
