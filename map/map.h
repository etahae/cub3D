/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:24:24 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/09 18:24:24 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

typedef struct s_cub_info{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	char	**map;
	int		f_int;
	int		c_int;
	int		player_x;
	int		player_y;
	char	player;
	int		map_rows;
	int		map_columns;
}	t_cub_info;

void	name_checker(char *path_name);
int		content_checker(char *path_name, t_cub_info *cub_info);
int		map_error(char *error_message, int error_value, t_cub_info *cub_info);
int		double_pointer_len(char **pointer);
void	texture_generator(t_cub_info	*cub_info, int fd);
void	freee(char	**pointer);
void	cub_info_struct_free(t_cub_info *cub_info);
void	get_map(char	*line, int fd, t_cub_info	*cub_info);
void	check_texture_files(t_cub_info	*cub_info);
void	rgb_check(t_cub_info	*cub_info);
int		skip_front_space(char	*line);
int		skip_back_space(char	*line);
void	invalid_map(t_cub_info	*cub_info, int x, int y);

#endif