/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:52 by paulohl           #+#    #+#             */
/*   Updated: 2021/01/10 15:31:27 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
** arg_count counts the number of arguments in a command.
*/

int			arg_count(char *str)
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
			while (str[i + 1] == ' ')
				i++;
		}
		if (str[i] == ' ' && !ft_strchr("<> ", str[i + 1]))
			count++;
		i = skip_quote(str, i);
		if (str[i] == '\\' && str[i + 1])
			i++;
		i++;
	}
	return (count);
}

void		reinit_struct(t_command *command)
{
	command->cmd = NULL;
	command->type_in = (command->pipe == PIPE_YES) ? '|' : ';';
	command->type_out = ';';
	command->pipe = PIPE_NO;
	set_redirect(command, '<', 0);
	set_redirect(command, '>', 1);
}

int			get_next_command(t_command *command, char *buffer)
{
	static int	i = 0;
	int			start;

	reinit_struct(command);
	if (!buffer && (i = 0) == 0)
		return (2);
	while (buffer[i] == ' ')
		i++;
	if (!buffer[i] && (i = 0) == 0)
		return (0);
	start = i--;
	while (buffer[++i] && buffer[i] != ';' && buffer[i] != '|')
	{
		i = skip_quote(buffer, i);
		if (buffer[i] == '\\' && buffer[i + 1])
			i++;
	}
	if (buffer[i] == '|' && (command->pipe = PIPE_YES))
		command->type_out = '|';
	else if (buffer[i] == ';')
		command->type_out = ';';
	if (buffer[i])
		buffer[i++] = 0;
	command->cmd = buffer + start;
	return (1);
}

int			parser(char *buffer, t_command *command)
{
	int			argc;
	char		*executable_path;
	char		**argv;

	while (get_next_command(command, buffer))
	{
		executable_path = 0;
		argc = arg_count(command->cmd);
		if (!(argv = parse_command(command, argc)))
			return (get_next_command(command, NULL));
		argv[argc] = 0;
		if (!(executable_path = get_executable_path(argv[0], command->env)))
			printf("couldn't find %s\n", argv[0]);
		else if (execute(executable_path, command, argv))
			printf("error: %s\n", strerror(errno));
		else if (!ft_strcmp(argv[0], "exit")
				&& (argv = free_argv(argv, argc, executable_path)) == 0)
			return (1);
		argv = free_argv(argv, argc, executable_path);
		argc = 0;
	}
	return (0);
}
