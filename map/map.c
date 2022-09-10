/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:18:02 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/09 18:18:02 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	border_walls_check(t_cub_info	*cub_info)
{
	int	x;
	int	len;

	len = double_pointer_len(cub_info->map);
	x = -1;
	while (cub_info->map[0][++x])
		if (cub_info->map[0][x] != ' ' && cub_info->map[0][x] != '1')
			map_error("north wall isn't compatible", EXIT_FAILURE, cub_info);
	x = -1;
	while (cub_info->map[len - 1][++x])
		if (cub_info->map[len - 1][x] != ' '
		&& cub_info->map[len - 1][x] != '1')
			map_error("south wall isn't compatible", EXIT_FAILURE, cub_info);
	x = -1;
	while (cub_info->map[++x])
		if (cub_info->map[x][skip_front_space(cub_info->map[x])] != '1'
		|| cub_info->map[x][skip_back_space(cub_info->map[x]) - 1] != '1')
			map_error("side wall isn't compatible", EXIT_FAILURE, cub_info);
}

int	is_player(char c)
{
	if (c != 'W' && c != 'S' && c != 'N' && c != 'E')
		return (0);
	return (1);
}

void	check_before_join(char	*line, t_cub_info *cub_info)
{
	int	x;

	x = -1;
	while (line[++x])
	{
		if (line[0] == '\n' || (line[x] != '1' && line[x] != '0'
				&& line[x] != ' ' && line[x] != '\n' && !is_player(line[x])))
		{
			map_error("map isn't compatible", EXIT_FAILURE, cub_info);
			free(line);
		}
	}
}

void	no_opened_space(t_cub_info *cub_info)
{
	int		x;
	size_t	y;
	int		player_count;

	x = -1;
	player_count = 0;
	while (cub_info->map[++x])
	{
		y = -1;
		while (cub_info->map[x][++y])
		{
			if (cub_info->map[x][y] == '0' || is_player(cub_info->map[x][y]))
				invalid_map(cub_info, x, y);
			if (is_player(cub_info->map[x][y]))
			{
				player_count++;
				if (player_count > 1)
					map_error("only 1 player allowed", EXIT_FAILURE, cub_info);
				cub_info->player_x = x;
				cub_info->player_y = y;
				cub_info->player = cub_info->map[x][y];
			}
		}
		if (y > cub_info->map_columns)
			cub_info->map_columns = y;
	}
	cub_info->map_rows = x - 1;
	if (player_count == 0)
		map_error("no player found", EXIT_FAILURE, cub_info);
}

void	get_map(char *line, int fd, t_cub_info *cub_info)
{
	char	*map;

	map = NULL;
	cub_info->map_rows = 0;
	cub_info->map_columns = 0;
	while (line)
	{
		check_before_join(line, cub_info);
		map = ft_strjoin(map, line);
		free(line);
		line = get_next_line(fd);
	}
	cub_info->map = ft_split(map, '\n');
	free(map);
	free(line);
	border_walls_check(cub_info);
	no_opened_space(cub_info);
}

/// ALL GOOOOOOD FOR NOW 5/9/2022 ..... SEE YA LATER !!!