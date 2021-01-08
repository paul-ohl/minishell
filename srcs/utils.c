/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 15:21:50 by pohl              #+#    #+#             */
/*   Updated: 2020/11/24 11:02:41 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

/*
** skip_quote increases the integer i until it reaches the corresponding quote
** in the string if buffer[i] equals " or ', ignoring if a '\' is present.
** example :
** buffer + i => "hi there's a cat here" text after
** i = skip_quote(buffer, i);
** buffer + i => " text after
*/

int			skip_quote(char *buffer, int i)
{
	char	to_skip;

	if ((buffer[i] != '"' && buffer[i] != '\''))
		return (i);
	to_skip = buffer[i];
	i++;
	if (to_skip == '\'')
		while (buffer[i] && buffer[i] != to_skip)
			i++;
	else
		while (buffer[i] && !(buffer[i] == to_skip && buffer[i - 1] != '\\'))
			i++;
	if (!buffer[i])
		i--;
	return (i);
}

/*
** skip_redirect increases the integer i until it reaches the end of the
** redirection.
** example :
** buffer + i => < redirection    other text
** i = skip_redirect(buffer, i);
** buffer + i =>     other text
*/

int			skip_redirect(char *buffer, int i)
{
	i++;
	if (buffer[i] == '>')
		i++;
	while (buffer[i] == ' ')
		i++;
	while (buffer[i] && buffer[i] != ' ')
	{
		if (buffer[i] == '\\')
			i++;
		else if (buffer[i] == '"' || buffer[i] == '\'')
			i = skip_quote(buffer, i);
		i++;
	}
	return (i);
}

t_command	*init_struct(char **envp)
{
	t_command	*command;

	if (!(command = malloc(sizeof(t_command))))
		return (0);
	command->cmd = NULL;
	command->fd_in = 0;
	command->fd_out = 1;
	command->type_in = ';';
	command->type_out = ';';
	command->pipe = PIPE_NO;
	command->return_value = 0;
	command->env = stock_env(envp);
	return (command);
}

void		set_redirect(t_command *command, char type, int redirect_fd)
{
	if (type == '<')
	{
		if (command->fd_in != 0)
			close(command->fd_in);
		command->fd_in = redirect_fd;
	}
	else
	{
		if (command->fd_out != 1)
			close(command->fd_out);
		command->fd_out = redirect_fd;
	}
}

int			ft_strcpy_free_input(char *dst, char *src, int to_free)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	if (to_free)
		free(src);
	return (i);
}
