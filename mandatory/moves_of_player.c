/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_of_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:44:52 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/10 18:26:01 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int move_player(t_player *p)
{
	p->distance = malloc(sizeof(double) * p->num_of_rays);
	p->ver.distance = malloc(sizeof(double) * p->num_of_rays);
	p->hor.distance = malloc(sizeof(double) * p->num_of_rays);
	p->px = malloc(sizeof(double) * p->num_of_rays);
	p->py = malloc(sizeof(double) * p->num_of_rays);
	p->if_is_vertical = malloc(sizeof(int) * p->num_of_rays);
	p->ver.i = 0;
	p->hor.i = 0;
	p->ray_angle = p->rotation_angle - (p->fov_angle / 2);
	p->angle_ray = malloc(sizeof(double) * p->num_of_rays);

	float next_x;
	float next_y;
	float move_step = p->walk * p->walk_speed;
	if(p->move != 0)
	{
		move_step = p->move * ( PI / 2);
		next_x = p->x +  (cos(p->rotation_angle  + move_step) * 5) ;
		next_y = p->y + (sin(p->rotation_angle + move_step) * 5) ;
	}
	else
	{
		next_x = p->x +  cos(p->rotation_angle) * move_step; 
		next_y = p->y + sin(p->rotation_angle) * move_step;
	}
	if(p->cub_info.map[(int)(next_y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] != '1')
	{
		p->x = next_x; 
		p->y = next_y;
	}
	find_intersections(p,0);
	return 0;
}


 

int	key_hook(int keycode, t_player *p)
{
	if(keycode == 124) 
	{
		p->turn = +1;
		p->rotation_angle += p->turn * p->turn_speed;
	}
	if(keycode == 123) 
	{
		p->turn = -1;
		p->rotation_angle += p->turn * p->turn_speed;
	}
	if(keycode == 13)// w
		p->walk = +1;
	if(keycode == 1)// s
		p->walk = -1;
	if(keycode == 0)// a
		p->move = -1; 
	if(keycode == 2) // d
		p->move = +1;
	return move_player(p);;
}

int	key_hook_s(int keycode, t_player *p)
{
 
	if(keycode == 124)
		p->turn = 0;
	if(keycode == 123)
		p->turn = 0; 
	if(keycode == 2)
		p->move = 0;
	if(keycode == 0) // d
		p->move = 0; 
	if(keycode == 13)
		p->walk = 0; 
	if(keycode == 1)// s
		p->walk = 0; 
	if (keycode == 53)
		cclose(p);
	return 0;
}

int moves_of_player(t_player *p)
{
	 
	mlx_hook(p->mlx.mlx_win, 02, 1L<<0, key_hook, p); 
	mlx_hook(p->mlx.mlx_win, 03, 1L<<0, key_hook_s, p); 

	return 1;
}
