/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:20:27 by nomoon            #+#    #+#             */
/*   Updated: 2021/02/07 20:00:19 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	count_argv(char **argv)
{
	int i;

	if (!argv)
		return (0);
	i = -1;
	while (argv[++i])
		;
	return (i);
}

void	builtin_exec(char *path, t_command *cmd, char **argv)
{
	cmd->return_value = 0;
	if (!path)
		cmd->return_value = 1;
	else if (!ft_strcmp(path, "pwd"))
		cmd->return_value = ft_pwd(cmd->env, argv);
	else if (!ft_strcmp(path, "env"))
		cmd->return_value = print_env(cmd->env, argv);
	else if (!ft_strcmp(path, "export"))
		cmd->return_value = export_check(cmd->env, argv);
	else if (!ft_strcmp(path, "unset"))
		cmd->return_value = unset(cmd->env, argv);
	else if (!ft_strcmp(path, "echo"))
		cmd->return_value = ft_echo(argv);
	else if (!ft_strcmp(path, "cd"))
		cmd->return_value = ft_cd(argv, cmd->env);
	else if (!ft_strcmp(path, "exit"))
		ft_exit(cmd->env, argv);
}

int	builtin_dup_selector(t_command *command, int new_pipe[2])
{
	if (command->type_in == '|')
	{
		close(command->pipe_fd[0]);
		close(command->pipe_fd[1]);
	}
	else if (command->type_in == '<')
		close(command->fd_in);
	if (command->type_out == '|')
		return (new_pipe[1]);
	else
		return (command->fd_out);
}

bool	builtin_handler(char *path, t_command *cmd, char **argv)
{
	int		fd_out;
	int		svg_fd;
	int		new_pipe[2];

	if ((cmd->type_out == '|' || cmd->pipe == PIPE_YES) && pipe(new_pipe))
		return (false);
	fd_out = builtin_dup_selector(cmd, new_pipe);
	if (fd_out != 1)
		svg_fd = dup(1);
	dup2(fd_out, 1);
	builtin_exec(path, cmd, argv);
	cmd->pipe_fd[0] = new_pipe[0];
	cmd->pipe_fd[1] = new_pipe[1];
	if (fd_out != 1)
	{
		close(fd_out);
		dup2(svg_fd, 1);
		close(svg_fd);
	}
	return (true);
}
