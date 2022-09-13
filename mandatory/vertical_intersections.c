/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:53:07 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/10 19:15:51 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	init_ver(t_player *p, int if_is_facing_left)
{
	p->ver.next_x = p->ver.x_intercept;
	p->ver.next_y = p->ver.y_intercept;
	if (if_is_facing_left)
		p->ver.next_x--;
	p->ver.found_wall = 0;
}

void	intersect_vertical_(t_player *p)
{
	if (p->ver.found_wall)
	{
		p->ver.distance[p->ver.i] = distance_calc(
				p->x, p->y, p->ver.next_x, p->ver.next_y);
	}
	else
		p->ver.distance[p->ver.i] = 10000000.444;
	p->ver.i++;
}

void	wall_intersect_vertical(t_player *p, int if_is_facing_left)
{
	init_ver(p, if_is_facing_left);
	while (point_in_range(p->ver.next_x, p->ver.next_y, p))
	{
		if (p->cub_info.map[(int)(p->ver.next_y / TILE_SIZE)]
		[(int)(p->ver.next_x / TILE_SIZE)] == '1')
		{
			p->ver.found_wall = 1;
			p->ver.wall_hit_y = p->ver.next_y;
			p->ver.wall_hit_x = p->ver.next_x;
			break ;
		}
		else
		{
			p->ver.next_y += p->ver.y_step;
			p->ver.next_x += p->ver.x_step;
		}
	}
	intersect_vertical_(p);
}

void	vertical_intersections_(t_player *p, int up, int down, int left)
{
	if (up && p->ver.y_step > 0)
		p->ver.y_step *= -1;
	else
		p->ver.y_step *= 1;
	if (down && p->ver.y_step < 0)
		p->ver.y_step *= -1;
	else
		p->ver.y_step *= 1;
	wall_intersect_vertical(p, left);
}

void	vertical_intersections(t_player *p)
{
	int	facing_up;
	int	facing_down;
	int	facing_right;
	int	facing_left;

	facing_down = (p->ray_angle > 0 && p->ray_angle < PI);
	facing_up = !facing_down;
	facing_right = (p->ray_angle < PI / 2 || p->ray_angle > (3 * PI) / 2);
	facing_left = !facing_right;
	p->ver.x_intercept = ((int)(p->x / TILE_SIZE)) * TILE_SIZE;
	if (facing_right)
		p->ver.x_intercept += TILE_SIZE;
	p->ver.y_intercept = p->y + (
			(p->ver.x_intercept - p->x) * tan(p->ray_angle));
	p->ver.x_step = TILE_SIZE;
	if (facing_left)
		p->ver.x_step *= -1;
	else
		p->ver.x_step *= 1;
	p->ver.y_step = TILE_SIZE * tan(p->ray_angle);
	vertical_intersections_(p, facing_up, facing_down, facing_left);
}
