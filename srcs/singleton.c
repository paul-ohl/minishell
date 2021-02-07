/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:38:12 by elbouju           #+#    #+#             */
/*   Updated: 2021/02/07 20:19:37 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_command	*singleton(void)
{
	static t_command	*cmd = NULL;

	if (cmd)
		return (cmd);
	cmd = ft_calloc(sizeof(t_command), 1);
	if (!cmd)
		return (NULL);
	return (cmd);
}
