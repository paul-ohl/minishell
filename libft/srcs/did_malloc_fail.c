/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   did_malloc_fail.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:49:40 by paulohl           #+#    #+#             */
/*   Updated: 2021/01/21 08:56:45 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	did_malloc_fail(void *buffer, size_t size)
{
	buffer = malloc(size);
	if (!buffer)
		return (0);
	else
		return (1);
}
