/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:14:27 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/09 18:14:27 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	lines_counter(char	*path)
{
	int		fd;
	int		counter;
	char	*line;

	line = NULL;
	counter = 0;
	fd = open(path, O_RDWR);
	if (fd == -1)
		exit(EXIT_FAILURE);
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		counter++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (counter);
}

int	content_checker(char *path_name, t_cub_info *cub_info)
{
	int	fd;
	int	lines_count;

	(void)cub_info;
	fd = open(path_name, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	lines_count = lines_counter(path_name);
	if (!lines_count)
		map_error("file is empty", EXIT_FAILURE, cub_info);
	texture_generator(cub_info, fd);
	close(fd);
	return (0);
}
