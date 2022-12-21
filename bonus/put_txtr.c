/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_txtr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:18:31 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/24 20:43:09 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	rgb_to_hex(int red, int green, int blue)
{
	int	hex;

	hex = red;
	hex += green << 8;
	hex += blue << 16;
	return (hex);
}

t_data	*get_txtr(t_game	*game)
{
	t_data	*tmp;

	if (game->ray.inter_door)
	{
		tmp = &game->txtr[4];
		return (tmp);
	}
	if (game->ray.hov)
	{
		if (game->ray.v_point.x < game->p.x)
			tmp = &game->txtr[2];
		else
			tmp = &game->txtr[3];
	}
	else
	{
		if (game->ray.v_point.y < game->p.y)
			tmp = &game->txtr[0];
		else
			tmp = &game->txtr[1];
	}
	return (tmp);
}

t_coords	get_coords(int x, int y)
{
	t_coords	x_y;

	x_y.x = x;
	x_y.y = y;
	return (x_y);
}

void	put_txtr(t_game *game, float lineH, float lineOff, float start)
{
	t_data		*tmp;
	t_coords	y_steps;
	int			pixel;
	static int	i;
	int			alpha;

	y_steps.x = 0;
	y_steps.y = -1;
	tmp = get_txtr(game);
	start = fmod(start, WALL_DIM) * tmp->width / WALL_DIM;
	alpha = game->ray.dist * 8;
	if (alpha > 255)
		alpha = 255;
	while (++y_steps.y < (int)lineH)
	{
		pixel = ((int)y_steps.x * tmp->line_length) + ((int)start * 4);
		my_mlx_pixel_put(&game->img, get_coords(i, lineOff + y_steps.y),
			rgb_to_hex(tmp->addr[pixel], tmp->addr[pixel + 1],
				tmp->addr[pixel + 2]), alpha);
		y_steps.x += tmp->height / lineH;
	}
	i++;
	if (i == RAYS_VIEW)
		i = 0;
}
