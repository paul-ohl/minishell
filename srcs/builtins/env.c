/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 08:53:18 by elbouju           #+#    #+#             */
/*   Updated: 2021/02/05 13:20:43 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../inc/minishell.h"
#include "../libft/libft.h"

int	len_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	env_error(char **argv)
{
	int i;

	i = 0;
	if (count_argv(argv) >= 2)
	{
		while (argv[i++])
		{
			if (argv[i][0] != '-' && ft_isprint(argv[i][0]))
			{
				printf("env: %s: No such file or directory\n", argv[i]);
				return (127);
			}
			else if (argv[1][0] == '-' && ft_isprint(argv[1][1]))
			{
				printf("env: illegal option -- %s\n", argv[1]);
				printf("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
				printf("[name=value ...] [utility [argument ...]]\n");
				return (1);
			}
		}
	}
	return (0);
}

int	print_env(t_env *env, char **argv)
{
	t_env	*tmp;
	int		err;

	err = env_error(argv);
	if (err != 0)
		return (err);
	tmp = env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

t_env	*stock_env(char **envp)
{
	int		i;
	t_env	*tmp;
	t_env	*new;
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	tmp = env;
	env->name = ft_substr(envp[0], 0, len_env(envp[0]));
	env->value = ft_substr(envp[0], len_env(envp[0]) + 1,
			ft_strlen(envp[0]) - len_env(envp[0]) - 1);
	i = 0;
	while (envp[++i])
	{
		if (!(new = malloc(sizeof(t_env))))
			return (NULL);
		new->name = ft_substr(envp[i], 0, len_env(envp[i]));
		new->value = ft_substr(envp[i], len_env(envp[i]) + 1,
				ft_strlen(envp[i]) - len_env(envp[i]) - 1);
		new->next = NULL;
		env->next = new;
		env = env->next;
	}
	env->next = NULL;
	return (tmp);
}
