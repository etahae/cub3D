/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:26:41 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/09 18:26:41 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	texture_nuller(t_cub_info *cub_info)
{
	cub_info->no = NULL;
	cub_info->so = NULL;
	cub_info->ea = NULL;
	cub_info->we = NULL;
	cub_info->f = NULL;
	cub_info->c = NULL;
	cub_info->map = NULL;
}

void	texture_assigner(t_cub_info *cub_info, char	**texture)
{
	if (!ft_strncmp(texture[0], "NO", 3))
		cub_info->no = ft_strdup(texture[1]);
	else if (!ft_strncmp(texture[0], "SO", 3))
		cub_info->so = ft_strdup(texture[1]);
	else if (!ft_strncmp(texture[0], "EA", 3))
		cub_info->ea = ft_strdup(texture[1]);
	else if (!ft_strncmp(texture[0], "WE", 3))
		cub_info->we = ft_strdup(texture[1]);
	else if (!ft_strncmp(texture[0], "F", 2))
		cub_info->f = ft_strdup(texture[1]);
	else if (!ft_strncmp(texture[0], "C", 2))
		cub_info->c = ft_strdup(texture[1]);
	else
		map_error("invalid element in file", EXIT_FAILURE, cub_info);
	if (texture[2] && ft_strncmp(texture[2], "\n", 2))
		map_error("invalid element in file", EXIT_FAILURE, cub_info);
}	

int	texture_checker(char	*texture, t_cub_info *cub_info)
{
	if ((ft_strncmp(texture, "NO", 3)
			&& ft_strncmp(texture, "WE", 3)
			&& ft_strncmp(texture, "SO", 3)
			&& ft_strncmp(texture, "EA", 3)
			&& ft_strncmp(texture, "F", 2)
			&& ft_strncmp(texture, "C", 2))
		|| (cub_info->c && cub_info->f && cub_info->ea
			&& cub_info->no && cub_info->we && cub_info->so))
		return (0);
	return (1);
}

char	*texture_assigner_caller(char	*line, t_cub_info *cub_info, int fd)
{
	char	**texture;

	while (line)
	{
		while (line && (!ft_strncmp("\r\n", line, 3)
				|| !ft_strncmp("\n", line, 2)))
		{
			free(line);
			line = get_next_line(fd);
		}
		if (line)
		{
			texture = ft_split(line, ' ');
			if (!texture_checker(texture[0], cub_info))
			{
				freee(texture);
				break ;
			}
			texture_assigner(cub_info, texture);
			freee(texture);
			free(line);
			line = get_next_line(fd);
		}
	}
	return (line);
}

void	texture_generator(t_cub_info *cub_info, int fd)
{
	char	*line;

	line = get_next_line(fd);
	texture_nuller(cub_info);
	line = texture_assigner_caller(line, cub_info, fd);
	if (!cub_info->c || !cub_info->f || !cub_info->no
		|| !cub_info->we || !cub_info->so || !cub_info->ea)
		map_error("a texture element is missing", EXIT_FAILURE, cub_info);
	check_texture_files(cub_info);
	rgb_check(cub_info);
	get_map(line, fd, cub_info);
}
