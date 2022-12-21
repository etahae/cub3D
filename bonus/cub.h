/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 10:52:18 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/27 15:21:37 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include "./map/map.h"

# define PI 3.141592653589793238
# define RAY_AN 0.001066590098418941
# define WIN_HEIGHT 720
# define WIN_WIDTH 1080
# define WALL_DIM 8
# define PLAYER_DIM 2
# define RAYS_VIEW WIN_WIDTH

// KEYS

# define CLOSE 1
# define OPEN 0

# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define A 0
# define S 1
# define D 2
# define W 13
# define Q 12
# define ESC 53

typedef struct s_player
{
	float	x;
	float	y;
	float	a;
	float	dx;
	float	dy;
}	t_player;

typedef struct s_coords
{
	float	x;
	float	y;
}	t_coords;

typedef struct s_ray
{
	int			hov;
	float		rx;
	float		ry;
	float		ra;
	float		xo;
	float		yo;
	float		dish;
	float		disv;
	float		dist;
	int			inter_door;
	t_coords	h_point;
	t_coords	v_point;
	t_coords	*f_point;
}	t_ray;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_door
{
	int		x;
	int		y;
	float	dp_dist;
	int		door_state;
	t_data	door_txtr;
}	t_door;

typedef struct s_game
{
	t_cub_info	cub_info;
	t_player	p;
	t_ray		ray;
	t_data		img;
	t_door		door;
	t_player	enemy;
	float		ep_dist;
	t_data		fire[8];
	t_data		txtr[5];
	char		**map;
	int			maplen;
	void		*win;
	void		*mlx_ptr;
}	t_game;

void		my_mlx_pixel_put(t_data *data, t_coords coords, int color,
				int alpha);
int			draw_map(t_game *game);
void		draw_wall(t_data *img, int i, int j, int color);
void		draw_player(t_data *img, int i, int j);
void		put_txtr(t_game *game, float lineH, float lineOff, float start);
int			rgb_to_hex(int red, int green, int blue);
int			hook(int keycode, t_game *game);
int			mouse_move(int x, int y, t_game *game);
void		fvip(t_game *game, int rayNum);
void		fhip(t_game *game, int rayNum);
void		find_dist(t_game *game, int rayNum);
void		draw_player(t_data *img, int i, int j);
void		draw_wall(t_data *img, int i, int j, int color);
void		mini_map(t_game *game);
void		ceifloor(t_game *game);
int			hand_draw(t_game *game);
void		anim_fire_out(t_game *game);
void		set_fire_imgs(t_game *game);
int			anim_fire(t_game *game);
t_coords	get_coords(int x, int y);
int			ft_exit(t_game *game);

#endif