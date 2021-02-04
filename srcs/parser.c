/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:52 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/04 14:43:40 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
** arg_count counts the number of arguments in a command.
*/

int	arg_count(char *str)
{
	int		i;
	int		count;

	i = 0;
	while (str[i] && str[i] == ' ')
		str++;
	if (!str[i])
		return (0);
	count = 1;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			i = skip_redirect(str, i);
			while (str[i] && str[i + 1] == ' ')
				i++;
		}
		if (str[i] == ' ' && !ft_strchr("<> ", str[i + 1]))
			count++;
		i = skip_quote(str, i);
		if (str[i] == '\\' && str[i + 1])
			i++;
		if (str[i])
			i++;
	}
	return (count);
}

void	reinit_struct(t_command *command)
{
	command->cmd = NULL;
	if (command->pipe == PIPE_YES)
		command->type_in = '|';
	else
		command->type_in = ';';
	command->type_out = ';';
	command->pipe = PIPE_NO;
	set_redirect_fd(command, '<', 0);
	set_redirect_fd(command, '>', 1);
}

bool	reset_counter(int *i, bool return_value)
{
	*i = 0;
	return (return_value);
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
	while (buffer[i] == ' ')
		i++;
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

void	print_executable_path_error(char *executable_path, t_command *command)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(executable_path, 2);
	ft_putstr_fd(": command not found\n", 2);
	command->return_value = 1;
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
		argv[argc] = 0;
		/* printf(">>>  for %s type_in: %c, type_out: %c, pipe: %c\n", command->cmd, command->type_in, command->type_out, command->pipe); */
		if (!(executable_path = get_executable_path(argv[0], command->env)))
			print_executable_path_error(argv[0], command);
		if (!execute(executable_path, command, argv))
			printf("error: %s\n", strerror(errno));
		argv = free_argv(argv, argc, executable_path);
		argc = 0;
	}
	printf("buffer: %s\n", buffer);
	return (true);
}
