/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoon <nomoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:52 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/18 18:23:20 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int	skip_initial_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

/*
 * get_next_command returns true while the end of the command has not been
 * reached.
 * exception: when buffer is NULL, it resets the counter i and returns false.
 */

int	get_next_command(t_command *command, char *buffer)
{
	static int	i = 0;
	int			start;

	reinit_struct(command);
	if (!buffer)
		return (reset_counter(&i, false));
	i += skip_initial_whitespaces(buffer + i);
	if (!buffer[i])
		return (reset_counter(&i, false));
	start = i--;
	while (buffer[++i] && buffer[i] != ';' && buffer[i] != '|')
	{
		i = skip_quote(buffer, i);
		if (buffer[i] == '\\')
			i++;
	}
	if (buffer[i] == '|')
	{
		command->pipe = PIPE_YES;
		command->type_out = '|';
	}
	if (buffer[i])
		buffer[i++] = 0;
	command->cmd = buffer + start;
	return (true);
}

void	print_executable_path_error(char *executable_path)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(executable_path, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_last_return = 1;
}

bool	parser(char *buffer, t_command *command)
{
	int			argc;
	char		*executable_path;
	char		**argv;

	while (get_next_command(command, buffer))
	{
		executable_path = 0;
		argc = arg_count(command->cmd);
		argv = parse_command(command, argc);
		if (!argv)
			continue ;
		if (argv[argc])
			free(argv[argc]);
		argv[argc] = 0;
		executable_path = get_executable_path(argv[0], command->env);
		if (!executable_path)
			print_executable_path_error(argv[0]);
		if (!execute(executable_path, command, argv))
			printf("error: %s\n", strerror(errno));
		argv = free_argv(argv, argc, executable_path);
		reset_fds(command);
		argc = 0;
	}
	return (true);
}
