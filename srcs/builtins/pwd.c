/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:16:15 by nomoon            #+#    #+#             */
/*   Updated: 2021/02/08 15:34:14 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../inc/minishell.h"
#include "../libft/libft.h"
#include <limits.h>

int	pwd_error(char *argv)
{
	if (ft_strlen(argv) > 1)
	{
		if (argv[0] == '-' && ft_isprint(argv[1]) && argv[1] != '-')
		{
			printf("bash: pwd: %c%c: invalid option", argv[0], argv[1]);
			printf("\npwd: usage: pwd [-LP]\n");
			return (1);
		}
	}
	return (0);
}

int	ft_pwd(t_env *env, char **argv)
{
	t_env	*tmp;
	char	cwd[PATH_MAX];

	tmp = env;
	if (count_argv(argv) >= 2)
		if (pwd_error(argv[1]) == 1)
			return (1);
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
