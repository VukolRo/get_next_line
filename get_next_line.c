/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shavok <shavok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:07:40 by shavok            #+#    #+#             */
/*   Updated: 2021/10/28 12:58:14 by shavok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 1

int	ft_strlen(const char *str)

{
	int	i;

	i = 0;
	if (!str)
		return(i);
	while (str[i] != '\0' )
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)

{
	int		i;
	char	*p;

	i = 0;
	p = (void *)0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
		{
			p = (void *)&str[i];
			return (p);
		}
		i++;
	}
	if (c == '\0')
		p = (void *)&str[i];
	return (p);
}


void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buf;
	size_t	i;
	char	*c;

	buf = (void *)malloc(nmemb * size);
	if (buf == NULL)
		return (NULL);
	else
		c = buf;
		i = 0;
		while (i++ < (nmemb * size))
			c[i] = '\0';
	return (buf);
}

char	*ft_strjoin(char const *s1, char const *s2)

{
	char	*buf;
	int		len_1;
	int		len_2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	buf = (char *)ft_calloc((len_1 + len_2 + 1), sizeof(char));
	if (buf)
	{
		i = -1;
		while (s1[++i])
			buf[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			buf[len_1] = s2[i];
			len_1++;
		}
	}
	return (buf);
}

char	*ft_strdup(char *src)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(src) + 1;
	dup = (char *)malloc((len) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	else
		while (i < ft_strlen(src))
		{
			dup[i] = src[i];
			i++;
		}
		dup[i] = '\0';
	return (dup);
}

static void	stc_rewrite_rest(char **rest, char **ptr)
{
	if (*ptr)
	{
		**ptr = '\0';
		if (!*rest)
		{
			free(*rest);
			*rest = NULL;
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

static void stc_last_check(int byte_was_read, char **line, char *rest)
{
	if (byte_was_read || ft_strlen(rest))
		stc_write_line(line, "\n");
	if (!(byte_was_read || ft_strlen(rest) || ft_strlen(*line)))
	{
		free(*line);
		*line = NULL;
	}
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
		if (!ptr)
			byte_was_read = read(fd, buf, BUFFER_SIZE);
		
		buf[byte_was_read] = '\0';
		ptr = ft_strchr(buf, '\n');
		stc_rewrite_rest(&rest, &ptr);
		stc_write_line(&line, buf);
	}
	stc_last_check(byte_was_read, &line, rest);
	return (line);
}

int main (void)
{
	int	fd;
	char *s;

	fd = open("nl", O_RDONLY);

	s = get_next_line(fd);
	printf("%s\n", s);
	return (0);
}