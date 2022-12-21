/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 11:16:02 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/25 09:17:59 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	anim_fire_out(t_game *game)
{
	static int	frame;
	int			x;
	int			y;

	x = WIN_WIDTH / 2 - game->fire[frame].width + 15;
	y = WIN_HEIGHT - hand_draw(game) - game->fire[frame].height;
	mlx_put_image_to_window(game->mlx_ptr, game->win, game->fire[frame].img,
		x, y);
	frame++;
	if (frame == 8)
		frame = 0;
}

int	mouse_move(int x, int y, t_game *game)
{
	(void)y;
	if (x < WIN_WIDTH && x > 0)
	{
		if (x > WIN_WIDTH / 2)
		{
			game->p.a += (0.10472 / 10) * ((x - WIN_WIDTH / 2) / 100);
			if (game->p.a >= 2 * PI)
				game->p.a -= 2 * PI;
			game->p.dx = cos(game->p.a) * 5;
			game->p.dy = sin(game->p.a) * 5;
		}
		if (x < WIN_WIDTH / 2)
		{
			game->p.a -= (0.10472 / 10) * ((WIN_WIDTH / 2 - x) / 100);
			if (game->p.a <= 0)
				game->p.a += 2 * PI;
			game->p.dx = cos(game->p.a);
			game->p.dy = sin(game->p.a);
		}
	}
	draw_map(game);
	anim_fire_out(game);
	return (0);
}
