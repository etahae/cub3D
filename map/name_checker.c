/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:25:47 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/09 18:25:47 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	valid_file(int fd, char	*file_name)
{
	if (fd == -1)
	{
		write(2, "cub3D: ", 7);
		write(2, "No such file or directory", 26);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(&file_name[ft_strlen(file_name) - 4], ".cub", 4))
	{
		write(2, "cub3D: ", 7);
		write(2, "Not a valid file", 17);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	name_checker(char *path_name)
{
	int	fd;

	fd = open(path_name, O_RDONLY);
	valid_file(fd, path_name);
	close(fd);
}
