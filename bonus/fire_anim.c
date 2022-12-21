/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:49:36 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/25 09:54:08 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	hand_draw(t_game *game)
{
	t_data	hand;

	hand.img = mlx_xpm_file_to_image(game->mlx_ptr, "sprites/hand.xpm",
			&hand.width, &hand.height);
	mlx_put_image_to_window(game->mlx_ptr, game->win, hand.img,
		WIN_WIDTH / 2 - hand.width, WIN_HEIGHT - hand.height);
	return (hand.height);
}

void	set_fire_imgs(t_game *game)
{
	game->fire[0].img = mlx_xpm_file_to_image(game->mlx_ptr,
			"sprites/fire1.xpm", &game->fire[0].width, &game->fire[0].height);
	game->fire[1].img = mlx_xpm_file_to_image(game->mlx_ptr,
			"sprites/fire2.xpm", &game->fire[1].width, &game->fire[1].height);
	game->fire[2].img = mlx_xpm_file_to_image(game->mlx_ptr,
			"sprites/fire3.xpm", &game->fire[2].width, &game->fire[2].height);
	game->fire[3].img = mlx_xpm_file_to_image(game->mlx_ptr,
			"sprites/fire4.xpm", &game->fire[3].width, &game->fire[3].height);
	game->fire[4].img = mlx_xpm_file_to_image(game->mlx_ptr,
			"sprites/fire5.xpm", &game->fire[4].width, &game->fire[4].height);
	game->fire[5].img = mlx_xpm_file_to_image(game->mlx_ptr,
			"sprites/fire6.xpm", &game->fire[5].width, &game->fire[5].height);
	game->fire[6].img = mlx_xpm_file_to_image(game->mlx_ptr,
			"sprites/fire7.xpm", &game->fire[6].width, &game->fire[6].height);
	game->fire[7].img = mlx_xpm_file_to_image(game->mlx_ptr,
			"sprites/fire8.xpm", &game->fire[7].width, &game->fire[7].height);
	if (!game->fire[0].img || !game->fire[1].img || !game->fire[2].img
		|| !game->fire[3].img || !game->fire[4].img || !game->fire[5].img
		|| !game->fire[6].img || !game->fire[7].img)
		map_error("corrupted texture files", EXIT_FAILURE, &game->cub_info);
}

int	anim_fire(t_game *game)
{
	static int	frame;
	int			hand_height;
	int			x;
	int			y;

	mlx_clear_window(game->mlx_ptr, game->win);
	draw_map(game);
	hand_height = hand_draw(game);
	x = WIN_WIDTH / 2 - game->fire[frame].width + 15;
	y = WIN_HEIGHT - hand_height - game->fire[frame].height;
	mlx_put_image_to_window(game->mlx_ptr, game->win, game->fire[frame].img,
		x, y);
	frame++;
	if (frame >= 8)
		frame = 0;
	return (0);
}
