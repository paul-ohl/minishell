/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:20:55 by pohl              #+#    #+#             */
/*   Updated: 2020/11/03 11:38:05 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strchr checks is character c is contained in const char *str.
** the function returns the char *str from the first occurence of c.
** It returns 0 if it doesn't find any occurence
*/

char	*ft_strchr(const char *str, char c)
{
	while (*str && *str != c)
		str++;
	if (*str == c)
		return ((char *)(str));
	return (0);
}
