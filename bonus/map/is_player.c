/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:33:37 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/11 17:33:52 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	is_player(char c)
{
	if (c != 'W' && c != 'S' && c != 'N' && c != 'E')
		return (0);
	return (1);
}
