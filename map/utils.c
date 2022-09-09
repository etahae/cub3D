/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:40:32 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/09 18:40:32 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	freee(char	**pointer)
{
	int	i;

	if (pointer)
	{
		i = -1;
		while (pointer[++i])
			free(pointer[i]);
	}
	free(pointer);
}

void	cub_info_struct_free(t_cub_info *cub_info)
{
	free(cub_info->no);
	free(cub_info->so);
	free(cub_info->ea);
	free(cub_info->we);
	free(cub_info->f);
	free(cub_info->c);
	freee(cub_info->map);
}

int	double_pointer_len(char **pointer)
{
	int	x;

	x = 0;
	while (pointer[x])
		x++;
	return (x);
}

int	skip_front_space(char	*line)
{
	int	x;

	x = 0;
	while (line[x] == ' ')
		x++;
	return (x);
}

int	skip_back_space(char	*line)
{
	int	x;

	x = ft_strlen(line);
	while (line[x - 1] == ' ')
		x--;
	return (x);
}
