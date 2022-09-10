/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:16:47 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/09 18:16:47 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	map_error(char	*error_message, int error_value, t_cub_info	*cub_info)
{
	if (error_message)
	{
		write(2, "cub3D: ", 7);
		write(2, error_message, ft_strlen(error_message));
	}
	cub_info_struct_free(cub_info);
	exit(error_value);
}

void	invalid_map(t_cub_info	*cub_info, int x, int y)
{
	if (y > ft_strlen(cub_info->map[x - 1]) - 1
		|| y > ft_strlen(cub_info->map[x + 1]) - 1)
		map_error("invalid map", EXIT_FAILURE, cub_info);
	if (cub_info->map[x][y + 1] == ' '
		|| cub_info->map[x][y - 1] == ' '
		|| cub_info->map[x + 1][y] == ' '
		|| cub_info->map[x - 1][y] == ' ')
		map_error("invalid map", EXIT_FAILURE, cub_info);
}
