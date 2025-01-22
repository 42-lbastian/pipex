/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:00:14 by Bastian           #+#    #+#             */
/*   Updated: 2021/11/24 15:00:18 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <stdlib.h>

char		**ft_split(char *s, char c);
int			ft_strlen(char *str);
char		*ft_strcat_path(char *str2, char *str1, int y);
char		*ft_strdup(char *s1);
int			ft_is_relative(char *str);

#endif
