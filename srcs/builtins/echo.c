/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:10:43 by nomoon            #+#    #+#             */
/*   Updated: 2021/01/14 08:55:43 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>
#include "../libft/libft.h"

static	int		nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int				ft_echo(t_env *env, char **args)
{
	int		i;
	int		n_option;

	i = 1;

	n_option = 0;
	if (nb_args(args) > 1)
	{
		while (args[i++] && ft_strcmp(args[i], "-n") == 0)
			n_option = 1;
		while (args[i++])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}