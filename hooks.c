/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:39:39 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/27 15:20:42 by aourhzal         ###   ########.fr       */
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
		game->p.x += game->p.dx;
		game->p.y += game->p.dy;
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
		game->p.x -= game->p.dx;
		game->p.y -= game->p.dy;
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
		if (game->map[y][x] != '1')
		{
			game->p.x += game->p.dy;
			game->p.y -= game->p.dx;
		}
	}
	if (keycode == D)
	{
		x = (int)(game->p.x - 1.5 * game->p.dy) / WALL_DIM;
		y = (int)(game->p.y + 1.5 * game->p.dx) / WALL_DIM;
		if (game->map[y][x] != '1')
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
	if (keycode == UP || keycode == W)
		forwards(game);
	else if (keycode == DOWN || keycode == S)
		backwards(game);
	if (keycode == A || keycode == D)
		sideways(game, keycode);
	if (keycode == RIGHT || keycode == LEFT)
		rotation(game, keycode);
	if (keycode == ESC || keycode == Q)
		ft_exit(game);
	draw_map(game);
	return (0);
}
