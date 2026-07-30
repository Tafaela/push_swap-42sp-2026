/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

#define GNL_BUF_SIZE 1024

static char	*extend_line(char *line, int *cap, int len)
{
	char	*new_line;
	int		i;

	*cap *= 2;
	new_line = (char *)malloc(*cap);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new_line[i] = line[i];
		i++;
	}
	free(line);
	return (new_line);
}

static char	*read_loop(int fd, char *line, int *cap)
{
	char	c;
	int		len;
	int		ret;

	len = 0;
	ret = read(fd, &c, 1);
	while (ret > 0 && c != '\n')
	{
		if (len + 1 >= *cap)
			line = extend_line(line, cap, len);
		if (!line)
			return (NULL);
		line[len++] = c;
		ret = read(fd, &c, 1);
	}
	if (len == 0 && ret <= 0)
	{
		free(line);
		return (NULL);
	}
	line[len] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;
	int		cap;

	cap = GNL_BUF_SIZE;
	line = (char *)malloc(cap);
	if (!line)
		return (NULL);
	return (read_loop(fd, line, &cap));
}
