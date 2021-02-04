/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:02:14 by nomoon            #+#    #+#             */
/*   Updated: 2021/02/04 17:19:15 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../inc/minishell.h"
#include "../libft/libft.h"
 
void	unset_loop(t_env *prev, t_env *env, char **argv)
{
	int	i;
	t_env	*tmp;
	
	i = 0;
	while (argv[++i])
	{
		tmp = env;
		prev = env->next;
		while (prev->next)
		{
			if (!ft_strcmp(argv[i], prev->name))
			{
				tmp->next = prev->next;
				break;
			}
			prev = prev->next;
			tmp = tmp->next;
		}
	}
}

int	unset(t_env *env, char **argv)
{
	t_env	*prev;
	int		i;

	i = 0;
	prev = env;
	while (argv[++i])
		if (!ft_strcmp(argv[i], prev->name))
			env = prev;
	prev = prev->next;
	unset_loop(prev, env, argv);
	return (0);
}
