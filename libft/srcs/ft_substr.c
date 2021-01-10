/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:02:15 by pohl              #+#    #+#             */
/*   Updated: 2021/01/10 16:32:07 by pohl             ###   ########.fr       */
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
		if (!(result = malloc(sizeof(string))))
			return (NULL);
		result[0] = 0;
		return (result);
	}
	if (!(result = malloc(sizeof(string) * ft_strlen(string + start) + 1)))
		return (NULL);
	i = -1;
	while (++i < len && string[start + i])
		result[i] = string[start + i];
	result[i] = 0;
	return (result);
}

// #include <stdio.h>

// int		start(void)
// {
// 	char *testest = ft_substr("char const *s", 2, 112);
// 	printf("%p, %s\n", testest, testest);
// 	free(testest);
// 	return (0);
// }

// int		main(void)
// {
// 	start();
// 	system("leaks useless");
// }