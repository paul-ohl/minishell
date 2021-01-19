/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:18:44 by pohl              #+#    #+#             */
/*   Updated: 2021/01/19 12:04:56 by paulohl          ###   ########.fr       */
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
	if ((fd = open(redirection, flags, 0000644)) == -1)
	{
		free(redirection);
		command->return_value = errno;
		return (0);
	}
	free(redirection);
	return (fd);
}

int	get_redirect(t_command *command, int *i)
{
	int		tmp;
	char	type;
	char	*redirect;

	type = command->cmd[(*i)];
	if (command->cmd[*i + 1] == '>' && (*i)++ != -42)
		type = 'a';
	if (type == '<')
		command->type_in = '<';
	else
		command->type_out = type;
	while (command->cmd[(*i) + 1] == ' ')
		(*i)++;
	tmp = skip_redirect(command->cmd, *i) - 1;
	if (!(redirect = get_word(command, (*i) + 1, tmp + 1)))
		return (0);
	*i = tmp;
	if (!(tmp = get_fd(redirect, type, command)))
		return (0);
	while (command->cmd[*i + 1] == ' ')
		(*i)++;
	if (!command->cmd[*i + 1])
		(*i)++;
	set_redirect(command, type, tmp);
	return (1);
}

int	increment_variables(char *str, int *i)
{
	while (str[*i] == ' ' && str[*i + 1] == ' ')
		(*i)++;
	if (str[*i + 1] == 0)
		(*i)++;
	return (*i);
}

char	**parse_command(t_command *command, int argc)
{
	int		i;
	int		j;
	int		start;
	char	**argv;

	if (!(argv = (char **)malloc(sizeof(argv) * (argc + 1))))
		return (NULL);
	i = -1;
	start = 0;
	j = 0;
	while ((i < 0 && ++i != -42) || command->cmd[i++])
	{
		i = skip_quote(command->cmd, i);
		if (reached_end_of_word(command->cmd + start, i - start))
		{
			if (!(argv[j++] = get_word(command, start, i)))
				return (NULL);
			start = increment_variables(command->cmd, &i);
		}
		if (command->cmd[i] == '>' || command->cmd[i] == '<')
			if (!(get_redirect(command, &i) && (start = i + 1) > -1))
				return (free_argv(argv, j, NULL));
		i = (command->cmd[i] == '\\' && command->cmd[i + 1]) ? i + 1 : i;
	}
	return (argv);
}
