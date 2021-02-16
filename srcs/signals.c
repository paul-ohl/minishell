/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoon <nomoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:37:15 by elbouju           #+#    #+#             */
/*   Updated: 2021/02/16 14:56:53 by nomoon           ###   ########.fr       */
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
	if (g_sig > 0)
		kill(g_sig, signal);
	g_last_return = status;
	if (tmp > -1 && WIFSIGNALED(status))
		write(1, "Quit: (core dumped)\n", 21);
}

void	sigint_handler(int signal)
{
	int	status;
	int	tmp;

	tmp = waitpid(-1, &status, WUNTRACED);
	if (tmp == -1 && g_sig == -1)
	{
		g_last_return = 130;
		return ;
	}
	if (g_sig > 0) //fork process id
		kill(g_sig, signal);
	g_last_return = status;
	if (tmp > -1 && WIFSIGNALED(status))
		write(1, "\n", 1);
	if (singleton()->cmd)
	{
		free(singleton()->cmd); //free
		singleton()->cmd = NULL;
	}
}
