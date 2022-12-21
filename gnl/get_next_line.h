/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:15:04 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/09 19:15:05 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*gnl_strjoin(char	*s1, char	*s2);
char	*gnl_strdup(char	*s);
char	*gnl_strchr(const char	*s, int c);
size_t	gnl_strlen(const char	*s);
char	*gnl_substr(char	*s, unsigned int start, size_t len);

#endif