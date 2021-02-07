/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:18:44 by pohl              #+#    #+#             */
/*   Updated: 2021/02/07 20:25:34 by paulohl          ###   ########.fr       */
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

int	increment_variables(char *str, int *i)
{
	while (str[*i] == ' ' && str[*i + 1] == ' ')
		(*i)++;
	if (str[*i + 1] == 0)
		(*i)++;
	return (*i);
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
