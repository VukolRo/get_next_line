/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shavok <shavok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:07:40 by shavok            #+#    #+#             */
/*   Updated: 2021/10/26 20:55:33 by shavok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


// static char	*stc_check_the_rest(char *rest_of_file, char **line)

// {
// 	char	*ptr_n;

// 	ptr_n = NULL;
// 	if (rest_of_file)
// 	{
// 		if ((ptr_n = ft_strchr(rest_of_file, '\n')))
// 		{
// 			*ptr_n = '\0';
// 			*line = ft_strdup(rest_of_file);
// 			ft_strcpy(rest_of_file, ++ptr_n);
// 		}
// 		else
// 		{
// 			*line = ft_strdup(rest_of_file); 
// 			ft_strclr(rest_of_file);
// 		}
// 	}
// 	else
// 		*line = (char *)ft_calloc(2, sizeof(char));
// 	return (ptr_n);
// }

// static char	*stc_get_the_line(int fd, char **line, char **rest_of_file, int size)

// {
// 	char		buf[size + 1];
// 	int			byte_was_read;
// 	char		*ptr_n;
// 	char		*tmp;

// 	ptr_n = stc_check_the_rest(*rest_of_file, line);

// 	while (!ptr_n && ((byte_was_read = read(fd, buf, size)) != -1))
// 	{
// 		buf[byte_was_read] = '\0';
// 		if ((ptr_n = ft_strchr(buf, '\n')))
// 		{
// 			*ptr_n = '\0';
// 			ptr_n++;
// 			*rest_of_file = ft_strdup(ptr_n);
// 		}
// 		tmp = *line;
// 		*line = ft_strjoin(*line, buf);
// 		free(tmp);
// 	}
// 	return (*line);
// }

// static t_struct	*stc_new_elm(int fd)

// {
// 	t_struct	*new;

// 	new = (t_struct *)ft_calloc(1, sizeof(t_struct));
// 	new->fd = fd;
// 	new->rest_of_file = NULL;
// 	new->next = NULL;
// 	return (new);
// }


static void	stc_rewrite_rest(char **rest, char **ptr)

{
	if (*ptr)
	{
		**ptr = '\0';
		if (*rest)
		{
			free(*rest);
			*rest = NULL;
		}
		*rest = ft_strdup(++(*ptr));
	}
}

static void	stc_write_line(char **line, const char *buf)

{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
}

static void stc_last_check(int byte_was_read, char **line, char *rest)

{
	if (byte_was_read || ft_strlen(rest))
		stc_write_line(line, "\n");
	if (!(byte_was_read || ft_strlen(rest) || ft_strlen(*line)))
		free(*line);
		*line = NULL;
}

static char	*stc_check_rest(char **rest, char **line)

{
	char	*ptr_n;
	char	*tmp;

	ptr_n = NULL;
	if (*rest)
	{
		ptr_n = ft_strchr(*rest, '\n'); 
		if (ptr_n)
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
			*rest = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (ptr_n);
}


char	*get_next_line(int fd)

{
	static char	*rest;
	char		*buf[BUFFER_SIZE + 1];
	char		*line;
	char		*ptr;
	int			byte_was_read;

	line = NULL;
	if (fd < 0)
	{	
		if (!(read(fd, 0, 0) < 0))
			return (NULL);
		ptr = stc_check_rest(&rest, &line);
		byte_was_read = 1;
		while (!ptr && byte_was_read)
		{
			byte_was_read = read(fd, buf, BUFFER_SIZE);
			buf[byte_was_read] = '\0';
			stc_rewrite_rest(&rest, &ptr);
			stc_write_line(&line, buf);
		}
		stc_last_check(byte_was_read, &line, rest);
	}
	return (line);
}