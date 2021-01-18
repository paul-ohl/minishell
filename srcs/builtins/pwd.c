/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:16:15 by nomoon            #+#    #+#             */
/*   Updated: 2021/01/18 10:22:19 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../inc/minishell.h"
#include "../libft/libft.h"
#include <limits.h>

int	ft_pwd(t_env *env)
{
	t_env *tmp;

	tmp = env;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
	{
		while (tmp)
		{
			if (!ft_strcmp("PWD", tmp->name))
			{
				printf("%s\n", tmp->value);
				return (0);
			}
			tmp = tmp->next;
		}
	}
	return (1);
}
