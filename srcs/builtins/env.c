/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 08:53:18 by elbouju           #+#    #+#             */
/*   Updated: 2021/01/14 10:17:07 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../inc/minishell.h"
#include "../libft/libft.h"

int len_env(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    return (i);
}

void    print_env(t_env *env)
{
    t_env   *tmp;
    tmp = env;

    while (tmp)
    {
        if (tmp->aff == 1)
        {
            ft_putstr_fd(tmp->name, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(tmp->value, 1);
            write(1, "\n", 1);
        }
        tmp = tmp->next;
    }
}

t_env   *stock_env(char **envp)
{
	int     i;
	t_env   *tmp;
	t_env   *new;
	t_env   *env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	tmp = env;
	env->name = ft_substr(envp[0], 0, len_env(envp[0]));
	env->value = ft_substr(envp[0], len_env(envp[0]) + 1,
			ft_strlen(envp[0]) - len_env(envp[0]) - 1);
    env->aff = 1;
	i = 0;
	while (envp[++i])
	{
		if (!(new = malloc(sizeof(t_env))))
			return (NULL);
		new->name = ft_substr(envp[i], 0, len_env(envp[i]));
		new->value = ft_substr(envp[i], len_env(envp[i]) + 1,
				ft_strlen(envp[i]) - len_env(envp[i]) - 1);
        new->aff = 1;
		new->next = NULL;
		env->next = new;
		env = env->next;
	}
	env->next = NULL;
	return (tmp);
}