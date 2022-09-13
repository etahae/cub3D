/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:04:17 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/11 18:14:28 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../map/map.h"
# include "../gnl/get_next_line.h"

# define PI 3.14159265358979323846

# define TILE_SIZE 64

typedef struct t_struct{
	char	*file;
	int		fd;
	int		i;
	int		j;
	int		x;
	int		len;
	char	*str;
}	t_m;

typedef struct t_h{
	double	wall_hit_x;
	double	wall_hit_y;
	double	next_x;
	double	next_y;
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	int		found_wall;
	double	*distance;
	int		i;
}	t_hor;

typedef struct t_v{
	double	wall_hit_y;
	double	wall_hit_x;
	double	next_x;
	double	next_y;
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	int		found_wall;
	double	*distance;
	int		i;
}	t_ver;

typedef struct t_wall{
	float	wall_strip_height;
	float	distance_project_plane;
	int		wall_top_px;
	int		wall_bottom_px;
	int		roof_px;
	int		floor_px;
	int		i;
	int		x;
	int		wall_strip_width;
}	t_wall;

typedef struct t_mini{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	void	*mlx;
	void	*mlx_win;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_mlx;

typedef struct t_textures{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	void	*mlx;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_tx;

typedef struct t_render_var
{
	int		distance_from_top;
	char	*dst;
	char	*src;
	t_tx	*texture;
	int		i;
}	t_render_vars;

typedef struct t_play
{
	int				win_width;
	int				win_height;
	double			ray_angle;
	double			x;
	double			y;
	double			rotation_angle;
	double			turn_speed;
	int				turn;
	int				walk;
	int				move;
	int				walk_speed;
	char			**lines;
	char			**pixels;
	double			*distance;
	int				num_of_rays;
	double			fov_angle;
	int				*if_is_vertical;
	double			*px;
	double			*py;
	char			*text_px;
	double			*angle_ray;
	int				width;
	t_m				map;
	t_hor			hor;
	t_ver			ver;
	t_wall			wall;
	t_mlx			mlx;
	t_cub_info		cub_info;
	t_render_vars	vars;
}t_player;

void	free_all(t_player *p, t_tx *texture);
void	normalize_rotation_angle(t_player *p);
int		cclose(t_player *p);
int		move_player(t_player *p, float next_x, float next_y, float move_step);
int		point_in_range(float x, float y, t_player *p);
void	my_mlx_pixel_put(t_player *data, int x, int y, int color);
void	draw_floor_roof(t_player *p);
void	alloc_pixels(t_player *p);
void	rendering_walls(t_player *p, int y, int x_offset, int y_offset);
double	distance_calc(double x1, double y1, double x2, double y2);
void	vertical_intersections(t_player *p);
void	horizontal_intersections(t_player *p);
void	find_intersections(t_player *p, int i);
void	put_player(t_player *p);
int		moves_of_player(t_player *p);
void	normalize_rotation_angle(t_player *p);
#endif