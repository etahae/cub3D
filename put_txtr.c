/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_txtr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:18:31 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/24 20:47:34 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

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
	float		steps;
	int			y;
	int			pixel;
	static int	i;

	steps = 0;
	y = -1;
	tmp = get_txtr(game);
	start = fmod(start, WALL_DIM) * tmp->width / WALL_DIM;
	while (++y < (int)lineH)
	{
		pixel = ((int)steps * tmp->line_length) + ((int)start * 4);
		my_mlx_pixel_put(&game->img, get_coords(i, lineOff + y),
			rgb_to_hex(tmp->addr[pixel], tmp->addr[pixel + 1],
				tmp->addr[pixel + 2]), 0);
		steps += tmp->height / lineH;
	}
	i++;
	if (i == RAYS_VIEW)
		i = 0;
}
