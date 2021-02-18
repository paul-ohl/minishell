/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reseter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:22:11 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/18 18:22:29 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
