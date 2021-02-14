/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:25 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/14 12:45:03 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

#define ERROR -1
#define NL_REACHED 0
#define CTRL_D 1

int	print_prompt(char **buf)
{
	int		input_return;

	write(1, "$> ", 3);
	*buf = NULL;
	input_return = get_user_input(buf);
	return (input_return);
}

int	start(int argc, char **argv, char **envp)
{
	char		*buf;
	int			err;
	t_command	*command;

	argc = 0;
	argv = NULL;
	if (!init_struct(envp, &command))
		return (GLOB_ERR_MALLOC);
	while (1)
	{
		if (print_prompt(&buf))
			ft_exit(command->env, NULL);
		printf("buff: %s\n", buf);
		if (!syntax_check(buf, &err, command))
			print_syntax_error(err);
		else
			parser(buf, command);
		if (buf)
			free(buf);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	g_sig = -1;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	return (start(argc, argv, envp));
}
