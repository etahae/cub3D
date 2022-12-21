/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:11:03 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/24 20:05:10 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	perfect_h(t_game *game, int rayNum)
{
	int	x;
	int	y;

	game->ray.f_point = &game->ray.h_point;
	x = (int)(game->ray.f_point->x / WALL_DIM);
	y = (int)(game->ray.f_point->y / WALL_DIM);
	game->ray.dist = game->ray.dish;
	if (rayNum == RAYS_VIEW / 2 && game->map[y][x] == 'D')
	{
		game->door.x = game->ray.f_point->x;
		game->door.y = game->ray.f_point->y;
		game->ray.inter_door = 1;
	}
	else if (game->map[y][x] == 'D' && game->door.door_state == CLOSE)
		game->ray.inter_door = 1;
	else
		game->ray.inter_door = 0;
	game->ray.hov = 0;
	if (game->ray.inter_door == 1 && rayNum == RAYS_VIEW / 2)
		game->door.dp_dist = game->ray.dist;
	else if (rayNum == RAYS_VIEW / 2)
		game->door.dp_dist = -1;
}

void	perfect_v(t_game *game, int rayNum)
{
	int	x;
	int	y;

	game->ray.f_point = &game->ray.v_point;
	x = (int)(game->ray.f_point->x / WALL_DIM);
	y = (int)(game->ray.f_point->y / WALL_DIM);
	game->ray.dist = game->ray.disv;
	if (rayNum == RAYS_VIEW / 2 && game->map[y][x] == 'D')
	{
		game->door.x = game->ray.f_point->x;
		game->door.y = game->ray.f_point->y;
		game->ray.inter_door = 1;
	}
	else if (game->map[y][x] == 'D' && game->door.door_state == CLOSE)
		game->ray.inter_door = 1;
	else
		game->ray.inter_door = 0;
	game->ray.hov = 1;
	if (game->ray.inter_door == 1 && rayNum == RAYS_VIEW / 2)
		game->door.dp_dist = game->ray.dist;
	else if (rayNum == RAYS_VIEW / 2)
		game->door.dp_dist = -1;
}

void	find_dist(t_game *game, int rayNum)
{
	if ((game->ray.dish < game->ray.disv
			|| !game->ray.disv) && game->ray.dish != 0)
		perfect_h(game, rayNum);
	else
		perfect_v(game, rayNum);
	if (game->door.dp_dist == -1 && (fabs(game->door.x - game->p.x) >= 13
			|| fabs(game->door.y - game->p.y) >= 13))
			game->door.door_state = CLOSE;
}
