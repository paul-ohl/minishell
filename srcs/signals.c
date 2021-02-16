/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoon <nomoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:37:15 by elbouju           #+#    #+#             */
/*   Updated: 2021/02/16 18:57:56 by nomoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	sigquit_handler(int signal)
{
	int	status;
	int	tmp;

	tmp = waitpid(-1, &status, WUNTRACED);
	if (tmp == -1)
	{
		write(1, "\b\b  \b\b", 6);
		return ;
	}
	if (g_fg_proc > 0)
		kill(g_fg_proc, signal);
	g_last_return = 131;
	if (tmp > -1 && WIFSIGNALED(status))
		write(1, "Quit: (core dumped)\n", 21);
}

void	sigint_handler(int signal)
{
	int	status;
	int	tmp;

	tmp = waitpid(-1, &status, WUNTRACED);
	if (tmp == -1 && g_fg_proc == -1)
	{
		write(1, "\b\b  \b\b\n$> ", 11);
		g_last_return = 130;
		return ;
	}
	if (g_fg_proc > 0)
		kill(g_fg_proc, signal);
	g_last_return = 130;
	if (tmp > -1 && WIFSIGNALED(status))
		write(1, "\n", 1);
	if (singleton()->cmd)
	{
		free(singleton()->cmd);
		singleton()->cmd = NULL;
	}
}
