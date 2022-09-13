/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 21:41:36 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/13 14:55:10 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	return_y(t_player *p)
{
	p->wall.distance_project_plane = (p->win_width / 2) / tan(p->fov_angle / 2);
	p->wall.wall_strip_height = (TILE_SIZE / p->distance[p->wall.i])
		* p->wall.distance_project_plane;
	if (p->wall.x % p->wall.wall_strip_width == 0 && p->wall.x != 0)
		p->wall.i++;
	p->wall.wall_top_px = (int)(p->win_height
			/ 2 - p->wall.wall_strip_height / 2);
	if (p->wall.wall_top_px < 0)
		p->wall.wall_top_px = 0;
	else
		p->wall.wall_top_px = p->wall.wall_top_px;
	p->wall.wall_bottom_px = (p->win_height
			/ 2 + p->wall.wall_strip_height / 2);
	if (p->wall.wall_bottom_px > p->win_height)
		p->wall.wall_bottom_px = p->win_height;
	else
		p->wall.wall_bottom_px = p->wall.wall_bottom_px;
	return (p->wall.wall_top_px);
}

static t_tx	*init_rend(t_player *p)
{
	t_tx	*textures;
	int		i;

	p->mlx.img = mlx_new_image(p->mlx.mlx, p->win_width, p->win_height);
	p->mlx.addr = mlx_get_data_addr(p->mlx.img, &p->mlx.bits_per_pixel,
			&p->mlx.line_length, &p->mlx.endian);
	textures = malloc(sizeof(t_tx) * 4);
	textures[0].img = mlx_xpm_file_to_image(p->mlx.mlx, p->cub_info.no,
			&textures[0].width, &textures[0].height);
	textures[1].img = mlx_xpm_file_to_image(p->mlx.mlx, p->cub_info.so,
			&textures[1].width, &textures[1].height);
	textures[2].img = mlx_xpm_file_to_image(p->mlx.mlx, p->cub_info.we,
			&textures[2].width, &textures[2].height);
	textures[3].img = mlx_xpm_file_to_image(p->mlx.mlx, p->cub_info.ea,
			&textures[3].width, &textures[3].height);
	if (!textures[0].img || !textures[1].img || !textures[2].img
		|| !textures[3].img)
		map_error("corrupted texture files", EXIT_FAILURE, &p->cub_info);
	i = -1;
	while (++i < 4)
		textures[i].addr = mlx_get_data_addr(textures[i].img,
				&textures[i].bits_per_pixel, &textures[i].line_length,
				&textures[i].endian);
	return (textures);
}

int	wall_direction(t_player *p)
{
	int	i;

	i = 0;
	if (p->if_is_vertical[p->wall.i] && p->px[p->wall.i] > p->x)
		i = 1;
	else if (p->if_is_vertical[p->wall.i] && p->px[p->wall.i] < p->x)
		i = 0;
	else if (!p->if_is_vertical[p->wall.i] && p->y > p->py[p->wall.i])
		i = 2;
	else if (!p->if_is_vertical[p->wall.i] && p->y < p->py[p->wall.i])
		i = 3;
	return (i);
}

void	rendering_walls_suite(t_player *p, int x_offset, int y_offset, int y)
{
	if (p->if_is_vertical[p->wall.i])
		x_offset = (fmod(p->py[p->wall.i], TILE_SIZE))
			* (p->vars.texture[p->vars.i].width / TILE_SIZE);
	else
		x_offset = (fmod(p->px[p->wall.i], TILE_SIZE))
			* (p->vars.texture[p->vars.i].width / TILE_SIZE);
	p->vars.distance_from_top
		= (y + (p->wall.wall_strip_height / 2) - (p->win_height / 2));
	y_offset = p->vars.distance_from_top
		* ((p->vars.texture[p->vars.i].height / p->wall.wall_strip_height));
	p->vars.dst = p->mlx.addr
		+ (y * p->mlx.line_length + p->wall.x * (p->mlx.bits_per_pixel / 8));
	p->vars.src = p->vars.texture[p->vars.i].addr
		+ (y_offset * p->vars.texture[p->vars.i].line_length
			+ x_offset * (p->vars.texture[p->vars.i].bits_per_pixel / 8));
	*(int *)p->vars.dst = *(int *)p->vars.src;
}

void	rendering_walls(t_player *p, int y, int x_offset, int y_offset)
{
	p->vars.texture = init_rend(p);
	p->wall.i = 0;
	p->wall.x = 0;
	p->wall.wall_strip_width = p->win_width / p->num_of_rays;
	while (p->wall.x < p->win_width)
	{
		y = return_y(p);
		p->vars.i = wall_direction(p);
		normalize_rotation_angle(p);
		while (y < p->wall.wall_bottom_px)
		{
			rendering_walls_suite(p, x_offset, y_offset, y);
			y++;
		}
		draw_floor_roof(p);
		p->wall.x++;
	}
	free_all(p, p->vars.texture);
}
