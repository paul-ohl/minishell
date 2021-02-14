/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:18:49 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/14 12:37:03 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 30
#endif
#define ERROR -1
#define NL_REACHED 0
#define CTRL_D 1

bool	append_str(char **dst, char *src)
{
	int		i;
	int		start;
	char	*new_str;

	if (*dst)
		start = ft_strlen(*dst);
	else
		start = 0;
	new_str = malloc(start + ft_strlen(src) + 1);
	if (!new_str)
		return (false);
	if (*dst)
		ft_strcpy(new_str, *dst);
	i = ft_strcpy(new_str + start, src);
	new_str[start + i] = 0;
	if (*dst)
		free(*dst);
	*dst = new_str;
	return (true);
}

bool	contains_nl(char **str)
{
	int		i;

	if (!*str || !**str)
		return (false);
	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
	{
		(*str)[i] = 0;
		return (true);
	}
	**str = 0;
	return (false);
}

int	get_user_input(char **line)
{
	int		read_len;
	int		total_read_len;
	char	*tmp_buffer;

	total_read_len = 0;
	tmp_buffer = malloc(BUFFER_SIZE + 1);
	if (!tmp_buffer)
		return (ERROR);
	tmp_buffer[0] = 0;
	while (!contains_nl(&tmp_buffer))
	{
		read_len = read(0, tmp_buffer, BUFFER_SIZE);
		total_read_len += read_len;
		if (!total_read_len)
		{
			free(tmp_buffer);
			return (CTRL_D);
		}
		tmp_buffer[read_len] = 0;
		if (!append_str(line, tmp_buffer))
			return (ERROR);
	}
	free(tmp_buffer);
	(*line)[total_read_len - 1] = 0;
	return (NL_REACHED);
}
