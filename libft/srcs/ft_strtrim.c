/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:51:37 by pohl              #+#    #+#             */
/*   Updated: 2021/01/26 12:08:29 by paulohl          ###   ########.fr       */
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

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*buffer;

	start = 0;
	if (!ft_strlen(s1))
		end = 0;
	else
		end = ft_strlen(s1) - 1;
	while (is_in_set(s1[start], set))
		start++;
	while (is_in_set(s1[end], set) && end > 0)
		end--;
	if (end == 0)
		start = end;
	else
		end++;
	if (!(buffer = malloc(end - start + 1)))
		return (0);
	i = -1;
	while (++i + start < end)
		buffer[i] = s1[start + i];
	buffer[end - start] = 0;
	return (buffer);
}
