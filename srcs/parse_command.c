/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:18:44 by pohl              #+#    #+#             */
/*   Updated: 2021/02/02 19:37:27 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	reached_end_of_word(char *str, int i)
{
	if (str[i] == ' ' || str[i] == 0)
		return (1);
	if (str[i] == '<' || str[i] == '>')
	{
		while (i-- > 0)
			if (str[i] != ' ')
				return (1);
	}
	return (0);
}

void	print_redirection_error(char *redirection)
{
	ft_putstr_fd("Minishell error: ", 2);
	ft_putstr_fd(redirection, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	free(redirection);
}

int	get_fd(char *redirection, char type, t_command *command)
{
	int		flags;
	int		fd;

	if (type == 'a')
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else if (type == '>')
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (type == '<')
		flags = O_RDONLY;
	else
		flags = 0;
	fd = open(redirection, flags, 0000644);
	if (fd == -1)
	{
		print_redirection_error(redirection);
		command->return_value = 1;
		return (0);
	}
	free(redirection);
	return (fd);
}

char	set_redirect_type(t_command *command, int *i)
{
	char	type;

	type = command->cmd[*i];
	if (command->cmd[*i + 1] == '>')
	{
		(*i)++;
		type = 'a';
	}
	if (type == '<')
		command->type_in = '<';
	else
		command->type_out = type;
	(*i)++;
	while (command->cmd[*i] == ' ')
		(*i)++;
	return (type);
}

bool	get_redirect(t_command *command, int *i)
{
	int		end_of_redirection;
	int		fd;
	char	type;
	char	*redirect;

	type = set_redirect_type(command, i);
	end_of_redirection = skip_redirect(command->cmd, *i);
	redirect = get_word(command, *i, end_of_redirection);
	if (!redirect)
		return (false);
	*i = end_of_redirection;
	fd = get_fd(redirect, type, command);
	if (!fd)
		return (false);
	set_redirect_fd(command, type, fd);
	return (true);
}

int	increment_variables(char *str, int *i)
{
	while (str[*i] == ' ' && str[*i + 1] == ' ')
		(*i)++;
	if (str[*i + 1] == 0)
		(*i)++;
	return (*i);
}

bool	handle_redirection(t_command *command, int *i, int *start)
{
	if (!get_redirect(command, i))
		return (false);
	while (command->cmd[*i] == ' ')
		(*i)++;
	(*i)--;
	*start = *i + 1;
	return (true);
}

bool	get_argv(char **argv, t_command *command)
{
	int		i;
	int		start;

	i = -1;
	start = 0;
	while ((i < 0 && ++i != -42) || command->cmd[i++])
	{
		i = skip_quote(command->cmd, i);
		if (reached_end_of_word(command->cmd + start, i - start))
		{
			*argv = get_word(command, start, i);
			if (!(argv)++)
				return (false);
			start = increment_variables(command->cmd, &i);
		}
		if (command->cmd[i] == '>' || command->cmd[i] == '<')
		{
			if (!handle_redirection(command, &i, &start))
				return (false);
		}
		if (command->cmd[i] == '\\')
			i++;
	}
	return (true);
}

char	**parse_command(t_command *command, int argc)
{
	char	**argv;

	argv = (char **)ft_calloc(argc + 1, sizeof(*argv));
	if (!argv)
		return (NULL);
	if (!get_argv(argv, command))
	{
		argc = 0;
		while (argv[argc])
			argc++;
		return (free_argv(argv, argc, NULL));
	}
	return (argv);
}
