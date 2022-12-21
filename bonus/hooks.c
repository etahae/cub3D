/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:39:39 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/27 15:44:00 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	forwards(t_game *game)
{
	int	x;
	int	y;

	x = (game->p.x + 1.5 * game->p.dx) / WALL_DIM;
	y = (game->p.y + 1.5 * game->p.dy) / WALL_DIM;
	if (game->map[y][x] != '1')
	{
		if (game->map[y][x] == 'D')
		{
			if (game->door.door_state == OPEN)
			{
				game->p.x += game->p.dx;
				game->p.y += game->p.dy;
			}
		}
		else
		{
			game->p.x += game->p.dx;
			game->p.y += game->p.dy;
		}
	}
}

void	backwards(t_game *game)
{
	int	x;
	int	y;

	x = (game->p.x - 1.5 * game->p.dx) / WALL_DIM;
	y = (game->p.y - 1.5 * game->p.dy) / WALL_DIM;
	if (game->map[y][x] != '1')
	{
		if (game->map[y][x] != '1')
		{
			if (game->map[y][x] == 'D')
			{
				if (game->door.door_state == OPEN)
				{
					game->p.x -= game->p.dx;
					game->p.y -= game->p.dy;
				}
			}
			else
			{
				game->p.x -= game->p.dx;
				game->p.y -= game->p.dy;
			}
		}
	}
}

void	sideways(t_game *game, int keycode)
{
	int	x;
	int	y;

	if (keycode == A)
	{
		x = (int)(game->p.x + 1.5 * game->p.dy) / WALL_DIM;
		y = (int)(game->p.y - 1.5 * game->p.dx) / WALL_DIM;
		if (game->map[y][x] == '0'
			|| (game->map[y][x] == 'D' && game->door.door_state == OPEN))
		{
			game->p.x += game->p.dy;
			game->p.y -= game->p.dx;
		}
	}
	if (keycode == D)
	{
		x = (int)(game->p.x - 1.5 * game->p.dy) / WALL_DIM;
		y = (int)(game->p.y + 1.5 * game->p.dx) / WALL_DIM;
		if (game->map[y][x] == '0'
			|| (game->map[y][x] == 'D' && game->door.door_state == OPEN))
		{
			game->p.x -= game->p.dy;
			game->p.y += game->p.dx;
		}
	}
}

void	rotation(t_game *game, int keycode)
{
	if (keycode == RIGHT)
	{
		game->p.a += 0.10472;
		if (game->p.a >= 2 * PI)
			game->p.a -= 2 * PI;
		game->p.dx = cos(game->p.a) * 5;
		game->p.dy = sin(game->p.a) * 5;
	}
	if (keycode == LEFT)
	{
		game->p.a -= 0.10472;
		if (game->p.a <= 0)
			game->p.a += 2 * PI;
		game->p.dx = cos(game->p.a) * 5;
		game->p.dy = sin(game->p.a) * 5;
	}
}

int	hook(int keycode, t_game *game)
{
	if (keycode == 49)
	{
		if (game->door.dp_dist <= 32 && game->door.dp_dist > 0)
			game->door.door_state = OPEN;
	}
	if (keycode == W)
		forwards(game);
	else if (keycode == S)
		backwards(game);
	if (keycode == A || keycode == D)
		sideways(game, keycode);
	if (keycode == RIGHT || keycode == LEFT)
		rotation(game, keycode);
	if (keycode == ESC || keycode == Q)
		ft_exit(game);
	draw_map(game);
	anim_fire_out(game);
	return (0);
}
