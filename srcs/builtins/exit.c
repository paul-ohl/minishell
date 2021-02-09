/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 08:42:59 by elbouju           #+#    #+#             */
/*   Updated: 2021/02/08 15:27:54 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	str_is_number(char *string)
{
	size_t	index;

	index = 0;
	while (string[index] != '\0')
	{
		if (string[index] < '0' || string[index] > '9')
			return (0);
		index++;
	}
	return (1);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		free(tmp->name);
		tmp->name = NULL;
		free(tmp->value);
		tmp->value = NULL;
		tmp = tmp->next;
	}
}

void	free_cmd(t_command *command)
{
	if (command->cmd)
		free(command->cmd);
	command->cmd = NULL;
}

void	ft_exit(t_env *env, char **argv)
{
	unsigned char	exit_code;

	exit_code = 1;
	printf("exit\n");
	if (count_argv(argv) >= 2)
	{
		if (str_is_number(argv[1]) == 1)
			exit_code = (unsigned char)ft_atoi(argv[1]);
		else
			printf("exit: First argument should be numeric.\n");
	}
	else
		exit_code = 0;
	free_env(env);
	exit(exit_code);
}
