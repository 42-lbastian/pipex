/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:51:43 by lbastian          #+#    #+#             */
/*   Updated: 2021/11/24 14:58:19 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tools.h"

int	ft_hm(char const *s, char c)
{
	size_t	nbr;
	int		i;

	nbr = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (i > 0 && s[i] && s[i - 1] == c)
			nbr++;
		if (s[i])
			i++;
	}
	if (nbr == 0 && s[i - 1] == c)
		return (0);
	if (s[0] != c)
		nbr++;
	return (nbr);
}

char	**ft_mal(char **strs, char *s, char c, int i)
{
	size_t	count;
	int		h;

	count = 0;
	h = -1;
	while (h++ < (ft_strlen(s) - 1))
	{
		if (s[h] != c)
			count++;
		else if (h > 0 && s[h - 1] != c)
		{
			strs[i] = malloc(sizeof(char) * (count + 1));
			if (!strs[i])
				return (0);
			count = 0;
			i++;
		}
		if (s[h + 1] == '\0' && s[h] != c)
		{
			strs[i] = malloc(sizeof(char) * count + 1);
			if (!strs)
				return (0);
		}
	}
	return (strs);
}

char	**ft_cpy(char **strs, char const *s, char c)
{
	int	i;
	int	j;
	int	h;

	i = 0;
	j = 0;
	h = 0;
	while (s[h])
	{
		if (s[h] != c)
			strs[i][j++] = s[h];
		else if (h > 0 && s[h - 1] != c)
		{
			if (h != 0)
			{
				strs[i][j] = '\0';
				j = 0;
				i++;
			}
		}
		if (s[h + 1] == '\0' && s[h] != c)
			strs[i][j] = '\0';
		h++;
	}
	return (strs);
}

char	**ft_split(char *s, char c)
{
	char	**rtn;
	int		nbr_w;

	if (!s || !*s)
	{
		rtn = malloc(sizeof(char *) * 1);
		if (!rtn)
			return (NULL);
		*rtn = (void *)0;
		return (rtn);
	}
	nbr_w = ft_hm(s, c);
	rtn = malloc(sizeof(char *) * (nbr_w + 1));
	if (!rtn)
		return (0);
	if (ft_mal(rtn, s, c, 0) != 0)
		ft_cpy(rtn, s, c);
	else
	{
		free(rtn);
		return (NULL);
	}
	rtn[nbr_w] = (void *)0;
	return (rtn);
}
