/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:51:37 by pohl              #+#    #+#             */
/*   Updated: 2021/02/09 15:07:02 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (42);
		i++;
	}
	return (0);
}

int	get_end(char const *s1)
{
	if (!ft_strlen(s1))
		return (0);
	else
		return (ft_strlen(s1) - 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*buffer;

	start = 0;
	end = get_end(s1);
	while (is_in_set(s1[start], set))
		start++;
	while (is_in_set(s1[end], set) && end > 0)
		end--;
	if (end == 0)
		start = end;
	else
		end++;
	buffer = malloc(end - start + 1);
	if (!buffer)
		return (0);
	i = -1;
	while (++i + start < end)
		buffer[i] = s1[start + i];
	buffer[end - start] = 0;
	return (buffer);
}
