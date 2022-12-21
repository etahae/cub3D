/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:03:44 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/24 20:48:53 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	fixeye(t_game *game)
{
	float	ca;

	ca = game->p.a - game->ray.ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	game->ray.dist *= cos(ca);
}

void	ray_draw(t_game *game)
{
	int		i;
	float	lineh;
	float	lineoff;

	i = -1;
	game->ray.ra = game->p.a - 0.575959;
	while (++i < RAYS_VIEW)
	{
		fvip(game);
		fhip(game);
		find_dist(game);
		fixeye(game);
		lineh = WIN_HEIGHT * WALL_DIM / game->ray.dist;
		if (lineh > WIN_HEIGHT)
			lineh = WIN_HEIGHT;
		lineoff = WIN_HEIGHT / 2 - lineh / 2;
		if (!game->ray.hov)
			put_txtr(game, lineh, lineoff, game->ray.f_point->x);
		else
			put_txtr(game, lineh, lineoff, game->ray.f_point->y);
		game->ray.ra += RAY_AN;
	}
}

int	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = game->p.y / WALL_DIM;
	x = game->p.x / WALL_DIM;
	mlx_destroy_image(game->mlx_ptr, game->img.img);
	mlx_clear_window(game->mlx_ptr, game->win);
	game->img.img = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_length, &game->img.endian);
	ceifloor(game);
	ray_draw(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win, game->img.img, 0, 0);
	return (0);
}
