/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:18:39 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/24 20:50:01 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	ceifloor(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIN_HEIGHT / 2)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			my_mlx_pixel_put(&game->img, get_coords(j, i),
				game->cub_info.c_int, 0);
	}
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			my_mlx_pixel_put(&game->img, get_coords(j, i),
				game->cub_info.f_int, 0);
	}
}
