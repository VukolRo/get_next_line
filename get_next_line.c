/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shavok <shavok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:07:40 by shavok            #+#    #+#             */
/*   Updated: 2021/10/23 20:46:36 by shavok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)

{
	char	*buff[BUFFER_SIZE];

	buff = (char *)malloc(BUFFER_SIZE * (sizeof(char)));
	
	if (fd)
	{

	}
	return (NULL);
}