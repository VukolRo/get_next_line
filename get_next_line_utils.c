/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shavok <shavok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:07:37 by shavok            #+#    #+#             */
/*   Updated: 2021/10/26 20:34:44 by shavok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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