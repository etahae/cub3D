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




void    wall_intersect_vertical(t_player *p,int if_is_facing_left)
{
    p->ver.next_x = p->ver.x_intercept;
    p->ver.next_y = p->ver.y_intercept;
    if(if_is_facing_left)
        p->ver.next_x--;
 
    p->ver.found_wall = 0;
    while (point_in_range(p->ver.next_x,p->ver.next_y, p))
    {

        if(p->cub_info.map[(int)(p->ver.next_y / TILE_SIZE)][(int)(p->ver.next_x / TILE_SIZE)] == '1')
        {
        
            p->ver.found_wall = 1;
            p->ver.wall_hit_y = p->ver.next_y;
            p->ver.wall_hit_x = p->ver.next_x;            
            break;
        }
        else
        {
            p->ver.next_y += p->ver.y_step;
            p->ver.next_x += p->ver.x_step;
        }
    }
    p->ver.distance[p->ver.i] = (p->ver.found_wall) ? distance_calc(p->x,p->y,p->ver.next_x,p->ver.next_y) : 10000000.444;
    p->ver.i++;
}




void vertical_intersections(t_player *p)
{
    int if_is_facing_up;
    int if_is_facing_down;
    int if_is_facing_right;
    int if_is_facing_left;

    if_is_facing_down = (p->ray_angle > 0 &&  p->ray_angle < PI);
    if_is_facing_up = !if_is_facing_down;
    if_is_facing_right = (p->ray_angle < PI / 2 || p->ray_angle > (3 * PI) / 2);
    if_is_facing_left = !if_is_facing_right;
    // find first closest point vertical
    p->ver.x_intercept = ((int)(p->x / TILE_SIZE)) * TILE_SIZE;
    if(if_is_facing_right)
        p->ver.x_intercept += TILE_SIZE;
    p->ver.y_intercept = p->y + ((p->ver.x_intercept - p->x) * tan(p->ray_angle));
    // calc xstep and ystep
    p->ver.x_step = TILE_SIZE; 
    p->ver.x_step *= (if_is_facing_left) ? -1 : 1;
    p->ver.y_step = TILE_SIZE * tan(p->ray_angle);
    p->ver.y_step *= (if_is_facing_up && p->ver.y_step > 0) ? -1 : 1;
    p->ver.y_step *= (if_is_facing_down && p->ver.y_step < 0) ? -1 : 1;

    wall_intersect_vertical(p,if_is_facing_left);
}