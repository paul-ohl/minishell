/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:46:23 by paulohl           #+#    #+#             */
/*   Updated: 2020/11/09 09:48:21 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** ft_strndup mallocs and returns the content of str, but only for len
** characters.
** It returns a NULL-terminated string.
*/

char		*ft_strndup(char *str, int len)
{
	char	*result;

	if (!(result = (char *)malloc(sizeof(result) * len + 1)))
		return (NULL);
	result = ft_memcpy(result, str, len);
	result[len] = 0;
	return (result);
}
