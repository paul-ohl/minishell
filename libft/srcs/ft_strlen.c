/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:37:13 by pohl              #+#    #+#             */
/*   Updated: 2021/02/14 12:39:21 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strlen(const char *str)
{
	const char	*initial_char;

	initial_char = str;
	while (*str)
		str++;
	return (str - initial_char);
}
