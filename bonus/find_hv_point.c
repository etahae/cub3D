/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_hv_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:08:34 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/25 10:49:38 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	door_intercpt(t_game	*game, int rayNum)
{
	if (game->door.door_state == OPEN && rayNum != RAYS_VIEW / 2)
	{
		game->ray.rx += game->ray.xo;
		game->ray.ry += game->ray.yo;
	}
	else if (game->door.door_state == CLOSE || rayNum == RAYS_VIEW / 2)
		return (1);
	return (0);
}

float	intercepoint(t_game	*game, int rayNum)
{
	int	x;
	int	y;

	x = (int)(game->ray.rx / WALL_DIM);
	y = (int)(game->ray.ry / WALL_DIM);
	while (y >= 0 && y < game->maplen && x < (int)ft_strlen(game->map[y]))
	{
		if (game->map[y][x] == 'D')
		{
			if (door_intercpt(game, rayNum))
				break ;
		}
		else if (game->map[y][x] == '1')
			break ;
		else
		{
			game->ray.rx += game->ray.xo;
			game->ray.ry += game->ray.yo;
		}
		x = (int)(game->ray.rx / WALL_DIM);
		y = (int)(game->ray.ry / WALL_DIM);
	}
	return (sqrt(pow(game->ray.rx - game->p.x, 2)
			+ pow(game->ray.ry - game->p.y, 2)));
}

void	fvip(t_game *game, int rayNum)
{
	float	atan;

	atan = tan(game->ray.ra);
	if (cos(game->ray.ra) < -0.01)
	{
		game->ray.rx = (((int)game->p.x >> 3) << 3) - 0.0001;
		game->ray.ry = (game->ray.rx - game->p.x) * atan + game->p.y;
		game->ray.xo = -WALL_DIM;
		game->ray.yo = game->ray.xo * atan;
	}
	else if (cos(game->ray.ra) > 0.01)
	{
		game->ray.rx = (((int)game->p.x >> 3) << 3) + WALL_DIM;
		game->ray.ry = (game->ray.rx - game->p.x) * atan + game->p.y;
		game->ray.xo = WALL_DIM;
		game->ray.yo = game->ray.xo * atan;
	}
	else
	{
		game->ray.rx = game->p.x;
		game->ray.ry = game->p.y;
	}
	game->ray.disv = intercepoint(game, rayNum);
	game->ray.v_point.x = game->ray.rx;
	game->ray.v_point.y = game->ray.ry;
}

void	fhip(t_game *game, int rayNum)
{
	float	atan;

	atan = 1 / tan(game->ray.ra);
	if (sin(game->ray.ra) < -0.01)
	{
		game->ray.ry = (((int)game->p.y >> 3) << 3) - 0.0001;
		game->ray.rx = (game->ray.ry - game->p.y) * atan + game->p.x;
		game->ray.yo = -WALL_DIM;
		game->ray.xo = game->ray.yo * atan;
	}
	else if (sin(game->ray.ra) > 0.01)
	{
		game->ray.ry = (((int)game->p.y >> 3) << 3) + WALL_DIM;
		game->ray.rx = (game->ray.ry - game->p.y) * atan + game->p.x;
		game->ray.yo = WALL_DIM;
		game->ray.xo = game->ray.yo * atan;
	}
	else
	{
		game->ray.rx = game->p.x;
		game->ray.ry = game->p.y;
	}
	game->ray.dish = intercepoint(game, rayNum);
	game->ray.h_point.x = game->ray.rx;
	game->ray.h_point.y = game->ray.ry;
}
