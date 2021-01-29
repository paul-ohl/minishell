/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:38:12 by elbouju           #+#    #+#             */
/*   Updated: 2021/01/29 10:40:00 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_command   *singleton(void)
{
	static t_command *cmd = NULL;

	if (cmd)
		return (cmd);
	if (!(cmd = ft_calloc(sizeof(t_command), 1)))
		return (NULL);
	return (cmd);
}