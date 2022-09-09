/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:14:41 by tnamir            #+#    #+#             */
/*   Updated: 2022/09/09 19:14:54 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

static char	*cpy_till_nl(char	*text)
{
	int		x;
	char	*l;

	if (text[0] == '\0')
		return (NULL);
	x = 0;
	while (text[x] != '\n' && text[x] != '\0')
		x++;
	l = malloc(x + 2);
	if (l == NULL)
		return (NULL);
	x = 0;
	while (text[x] != '\n' && text[x] != '\0')
	{
		l[x] = text[x];
		x++;
	}
	if (text[x] == '\n')
	{
		l[x] = '\n';
		l[x + 1] = '\0';
	}
	else
		l[x] = '\0';
	return (l);
}

static char	*del_till_nl(char	*text)
{
	int		x;
	char	*p;

	x = 0;
	if (text[0] == '\0')
	{
		free(text);
		return (NULL);
	}
	while (text[x] != '\n' && text[x] != '\0')
		x++;
	x++;
	p = gnl_substr(text, x, strlen(text) - x);
	free(text);
	return (p);
}

static char	*study(int fd, char *text)
{
	int		size;
	char	*line;

	size = 1;
	while (size != 0 && !gnl_strchr(text, '\n'))
	{
		line = malloc(BUFFER_SIZE + 1);
		if (line == NULL)
			return (NULL);
		size = read(fd, line, BUFFER_SIZE);
		if (size == -1)
		{
			free(line);
			return (NULL);
		}
		line[size] = '\0';
		text = gnl_strjoin(text, line);
		free(line);
	}
	return (text);
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*perfectline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	text = study(fd, text);
	if (text == NULL)
		return (NULL);
	perfectline = cpy_till_nl(text);
	text = del_till_nl(text);
	return (perfectline);
}
