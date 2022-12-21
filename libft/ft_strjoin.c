/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:58:42 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/03 13:05:35 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const	*s1, char const	*s2)
{
	char		*p;
	size_t		x;
	size_t		y;

	y = 0;
	x = 0;
	p = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (p == NULL)
		return (0);
	while (x < ft_strlen(s1))
	{
		p[x] = s1[x];
		x++;
	}
	while (y <= ft_strlen(s2))
		p[x++] = s2[y++];
	free((char *)s1);
	return (p);
	return (0);
}
