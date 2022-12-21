/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:18:39 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/24 20:45:26 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_wall(t_data *img, int i, int j, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WALL_DIM)
	{
		y = 0;
		while (y < WALL_DIM)
		{
			my_mlx_pixel_put(img, get_coords(x + i, y + j), color, 0);
			y++;
		}
		x++;
	}
}

void	draw_player(t_data *img, int i, int j)
{
	int	x;
	int	y;

	x = 0;
	while (x < PLAYER_DIM)
	{
		y = 0;
		while (y < PLAYER_DIM)
		{
			my_mlx_pixel_put(img,
				get_coords(x + i - PLAYER_DIM / 2, y + j - PLAYER_DIM / 2),
				0x0000FF00, 0);
			y++;
		}
		x++;
	}
}

void	mini_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
				draw_wall(&game->img, j * WALL_DIM, i * WALL_DIM, 0x99FFFFFF);
			else if (game->map[i][j] == 'D')
				draw_wall(&game->img, j * WALL_DIM, i * WALL_DIM, 0xFF0000);
			else if (game->map[i][j] != ' ')
				draw_wall(&game->img, j * WALL_DIM, i * WALL_DIM, 0x990000FF);
			j++;
		}
		i++;
	}
}

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
