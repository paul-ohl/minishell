/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:02:15 by pohl              #+#    #+#             */
/*   Updated: 2021/01/21 10:09:29 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *string, unsigned int start, size_t len)
{
	size_t	i;
	size_t	string_len;
	char	*result;

	if (!string)
		return (NULL);
	string_len = ft_strlen(string);
	if (start >= string_len)
	{
		result = malloc(sizeof(string));
		if (!result)
			return (NULL);
		result[0] = 0;
		return (result);
	}
	result = malloc(sizeof(string) * ft_strlen(string + start) + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len && string[start + i])
		result[i] = string[start + i];
	result[i] = 0;
	return (result);
}
