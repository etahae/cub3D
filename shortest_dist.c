/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:11:03 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/24 20:49:25 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	find_dist(t_game *game)
{
	if ((game->ray.dish < game->ray.disv
			|| !game->ray.disv) && game->ray.dish != 0)
	{
		game->ray.f_point = &game->ray.h_point;
		game->ray.dist = game->ray.dish;
		game->ray.hov = 0;
	}
	else
	{
		game->ray.f_point = &game->ray.v_point;
		game->ray.dist = game->ray.disv;
		game->ray.hov = 1;
	}
}
