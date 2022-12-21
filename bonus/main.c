/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:09:27 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/25 11:14:43 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_exit(t_game *game)
{
	cub_info_struct_free(&game->cub_info);
	exit(0);
}

float	find_angle(char a)
{
	if (a == 'S')
		return (0.5 * PI);
	else if (a == 'N')
		return (1.5 * PI);
	else if (a == 'W')
		return (PI);
	else
		return (0);
}	

void	init_parse(t_game *game)
{
	game->map = game->cub_info.map;
	game->maplen = game->cub_info.map_rows + 1;
	game->p.x = game->cub_info.player_y * WALL_DIM + 4;
	game->p.y = game->cub_info.player_x * WALL_DIM + 4;
	if (game->cub_info.enemy_x != -1 && game->cub_info.enemy_x != -1)
	{
		game->enemy.x = game->cub_info.enemy_x * WALL_DIM;
		game->enemy.y = game->cub_info.enemy_y * WALL_DIM;
	}
	game->p.a = find_angle(game->cub_info.player);
	game->p.dx = cos(game->p.a) * 5;
	game->p.dy = sin(game->p.a) * 5;
}

void	set_txts_img(t_game *game)
{
	int		i;

	game->txtr[0].img = mlx_xpm_file_to_image(game->mlx_ptr, game->cub_info.no,
			&game->txtr[0].width, &game->txtr[0].height);
	game->txtr[1].img = mlx_xpm_file_to_image(game->mlx_ptr, game->cub_info.so,
			&game->txtr[1].width, &game->txtr[1].height);
	game->txtr[2].img = mlx_xpm_file_to_image(game->mlx_ptr, game->cub_info.we,
			&game->txtr[2].width, &game->txtr[2].height);
	game->txtr[3].img = mlx_xpm_file_to_image(game->mlx_ptr, game->cub_info.ea,
			&game->txtr[3].width, &game->txtr[3].height);
	game->txtr[4].img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./sprites/door.xpm", &game->txtr[4].width, &game->txtr[4].height);
	if (!game->txtr[0].img || !game->txtr[1].img || !game->txtr[2].img
		|| !game->txtr[3].img || !game->txtr[4].img)
		map_error("corrupted texture files", EXIT_FAILURE, &game->cub_info);
	i = -1;
	while (++i < 5)
		game->txtr[i].addr = mlx_get_data_addr(game->txtr[i].img,
				&game->txtr[i].bpp, &game->txtr[i].line_length,
				&game->txtr[i].endian);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (0);
	name_checker(av[1]);
	content_checker(av[1], &game.cub_info);
	game.door.door_state = CLOSE;
	init_parse(&game);
	game.mlx_ptr = mlx_init();
	game.win = mlx_new_window(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	set_txts_img(&game);
	set_fire_imgs(&game);
	game.img.img = mlx_new_image(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img,
			&game.img.bpp, &game.img.line_length, &game.img.endian);
	mlx_hook(game.win, 02, 0, hook, &game);
	mlx_hook(game.win, 06, 0, mouse_move, &game);
	mlx_loop_hook(game.mlx_ptr, anim_fire, &game);
	mlx_hook(game.win, 17, 0, ft_exit, &game);
	mlx_loop(game.mlx_ptr);
}
