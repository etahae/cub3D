/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhzal <aourhzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:10:34 by aourhzal          #+#    #+#             */
/*   Updated: 2022/10/26 17:51:09 by aourhzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_data *data, t_coords coords, int color, int alpha)
{
	int	pixel;

	pixel = (coords.y * data->line_length) + (coords.x * data->bpp / 8);
	data->addr[pixel + 0] = color;
	data->addr[pixel + 1] = color >> 8;
	data->addr[pixel + 2] = color >> 16;
	data->addr[pixel + 3] = alpha;
}
