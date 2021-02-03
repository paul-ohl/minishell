/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 06:34:05 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/02 15:21:04 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	free_everything(char *buf, t_command *command)
{
	t_env	*tmp;

	free(buf);
	reset_fds(command);
	while (command->env)
	{
		tmp = command->env->next;
		free(command->env->name);
		free(command->env->value);
		free(command->env);
		command->env = tmp;
	}
	free(command->env);
	free(command);
}

char	**free_argv(char **argv, int argc, char *executable_path)
{
	while (argc-- && argv[argc])
		free(argv[argc]);
	free(argv);
	if (executable_path)
		free(executable_path);
	return (NULL);
}

void	reset_fds(t_command *command)
{
	if (command->fd_in != 0)
		close(command->fd_in);
	if (command->fd_out != 1)
		close(command->fd_out);
}

char	**free_envp(char **envp, int end)
{
	int		i;

	i = -1;
	while (++i < end)
		free(envp[i]);
	free(envp);
	return (NULL);
}
