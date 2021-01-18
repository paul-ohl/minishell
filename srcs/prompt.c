/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:25 by paulohl           #+#    #+#             */
/*   Updated: 2021/01/18 18:55:01 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int		print_prompt(char *buf)
{
	int		n;

	write(1, "$> ", 3);
	n = read(0, buf, MAX_CMD_LEN);
	buf[n - 1] = 0;
	if (n == MAX_CMD_LEN)
		return (0);
	return (n);
}

int		exit_return(char *buf, t_command *command)
{
	int		exit_value;
	t_env	*tmp;

	exit_value = command->return_value;
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
	return (exit_value);
}

int		start(int argc, char **argv, char **envp)
{
	char		*buf;
	int			err;
	t_command	*command;

	argc = 0;
	argv = NULL;
	if (!(buf = (char *)malloc(sizeof(*buf) * MAX_CMD_LEN)))
		return (GLOB_ERR_MALLOC);
	if (!(command = init_struct(envp)))
		return (GLOB_ERR_MALLOC);
	while (1)
	{
		if (!print_prompt(buf))
			return (GLOB_CMD_LEN);
		if ((err = basic_syntax_check(buf)))
			print_syntax_error(err);
		else if ((err = parser(buf, command)) == 1)
			return (exit_return(buf, command));
		else if (err)
			print_parser_error(err, command);
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	return(start(argc, argv, envp));
	start(argc, argv, envp);
	system("leaks minishell");
}
