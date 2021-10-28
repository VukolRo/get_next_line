/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shavok <shavok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:07:40 by shavok            #+#    #+#             */
/*   Updated: 2021/10/28 17:07:13 by shavok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	stc_rewrite_rest(char **rest, char **ptr)
{
	if (*ptr != 0)
	{
		**ptr = '\0';
		if (*rest != 0)
		{
			free(*rest);
			*rest = 0;
		}
		*rest = ft_strdup(++(*ptr));
	}
}

static void	stc_write_line(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
}

static void	stc_last_check(int byte_was_read, char **line, char *rest)
{
	if (byte_was_read || ft_strlen(rest))
		stc_write_line(&(*line), "\n");
	if (byte_was_read || ft_strlen(rest) || ft_strlen(*line))
		return ;
	else
	{
		free(*line);
		*line = 0;
	}
}

static char	*stc_check_rest(char **rest, char **line)
{
	char	*ptr_n;
	char	*tmp;

	ptr_n = 0;
	if (*rest)
	{
		ptr_n = ft_strchr(*rest, '\n');
		if (ptr_n != 0)
		{
			*ptr_n = '\0';
			*line = ft_strdup(*rest);
			tmp = *rest;
			*rest = ft_strdup(++ptr_n);
			free(tmp);
		}
		else
		{
			*line = ft_strdup(*rest);
			free(*rest);
			*rest = 0;
		}
	}
	else
		*line = ft_strdup("");
	return (ptr_n);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	char		*ptr;
	int			byte_was_read;

	if ((read(fd, 0, 0) < 0))
		return (NULL);
	ptr = stc_check_rest(&rest, &line);
	byte_was_read = 1;
	while (!ptr && byte_was_read)
	{
		byte_was_read = read(fd, buf, BUFFER_SIZE);
		buf[byte_was_read] = '\0';
		ptr = ft_strchr(buf, '\n');
		stc_rewrite_rest(&rest, &ptr);
		stc_write_line(&line, buf);
	}
	stc_last_check(byte_was_read, &line, rest);
	return (line);
}
