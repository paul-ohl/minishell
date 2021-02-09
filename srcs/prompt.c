/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:25 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/09 15:03:15 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int	print_prompt(char *buf)
{
	int		n;

	write(1, "$> ", 3);
	n = read(0, buf, MAX_CMD_LEN);
	if (!n)
		return (0);
	buf[n - 1] = 0;
	return (n);
}

int	start(int argc, char **argv, char **envp)
{
	char		*buf;
	int			err;
	t_command	*command;

	argc = 0;
	argv = NULL;
	buf = (char *)malloc(sizeof(*buf) * MAX_CMD_LEN);
	if (!buf)
		return (GLOB_ERR_MALLOC);
	if (!init_struct(envp, &command))
		return (GLOB_ERR_MALLOC);
	while (1)
	{
		if (!print_prompt(buf))
			ft_exit(command->env, NULL);
		if (!syntax_check(buf, &err, command))
			print_syntax_error(err);
		else
			parser(buf, command);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	g_sig = -1;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	return (start(argc, argv, envp));
	return (singleton()->return_value);
	start(argc, argv, envp);
}
