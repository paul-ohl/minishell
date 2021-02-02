/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:31:25 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/02 11:44:07 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	dup_selector(int to_dup[2], t_command *command, int new_pipe_out)
{
	to_dup[0] = 0;
	to_dup[1] = 1;
	if (command->type_in == '|')
		to_dup[0] = command->pipe_fd[0];
	else if (command->type_in == '<')
		to_dup[0] = command->fd_in;
	if (command->type_out == '|')
		to_dup[1] = new_pipe_out;
	else if (command->type_out == '>' || command->type_out == 'a')
		to_dup[1] = command->fd_out;
}

int		slave_action(int to_dup[2], t_command *cmd, char *path, char **argv)
{
	char	**envp;

	dup2(to_dup[0], 0);
	dup2(to_dup[1], 1);
	if (cmd->type_in == '|')
	{
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
	}
	envp = to_string_array(cmd->env);
	if (!envp)
		return (false);
	else if (execve(path, argv, envp))
		printf("Problem: %s\n", strerror(errno));
	exit(1);
	return (true);
}

bool	program_handler(char *path, t_command *cmd, char **argv)
{
	int		to_dup[2];
	int		new_pipe[2];
	pid_t	pid;

	if ((cmd->type_out == '|' || cmd->pipe == PIPE_YES) && pipe(new_pipe))
		return (false);
	pid = fork();
	if (pid < 0)
		return (false);
	dup_selector(to_dup, cmd, new_pipe[1]);
	if (pid == 0)
		return (slave_action(to_dup, cmd, path, argv));
	else
	{
		if (cmd->type_in == '|')
		{
			close(cmd->pipe_fd[0]);
			close(cmd->pipe_fd[1]);
		}
		waitpid(pid, &cmd->return_value, 0);
		cmd->pipe_fd[0] = new_pipe[0];
		cmd->pipe_fd[1] = new_pipe[1];
	}
	return (true);
}

bool	execute(char *path, t_command *cmd, char **argv)
{
	if (is_builtin(path))
		builtin_handler(path, cmd, argv);
	else if (!program_handler(path, cmd, argv))
		return (false);
	return (true);
}
