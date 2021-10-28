/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shavok <shavok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:07:35 by shavok            #+#    #+#             */
/*   Updated: 2021/10/28 12:54:45 by shavok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h> //for "open"
# include <stdio.h> //for printf

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 1
// # elif BUFFER_SIZE < 1
// #  undef BUFFER_SIZE
// #  define BUFFER_SIZE 1
// # endif


char	*get_next_line(int fd);

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char *src);
char	*ft_strchr(const char *str, int c);

#endif