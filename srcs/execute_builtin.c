/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:20:27 by nomoon            #+#    #+#             */
/*   Updated: 2021/02/09 12:43:27 by paulohl          ###   ########.fr       */
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
	int	i;

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

int	builtin_dup_selector(int to_dup[2], t_command *cmd, int pipe, int svg_fd[2])
{
	to_dup[0] = 0;
	to_dup[1] = 1;
	if (cmd->type_in == '|')
		to_dup[0] = cmd->pipe_fd[0];
	else if (cmd->type_in == '<')
		to_dup[0] = cmd->fd_in;
	if (cmd->type_out == '|')
		to_dup[1] = pipe;
	else if (cmd->type_out == '>' || cmd->type_out == 'a')
		to_dup[1] = cmd->fd_out;
	if (to_dup[1] != 1)
		svg_fd[1] = dup(1);
	if (to_dup[0] != 0)
		svg_fd[0] = dup(0);
	return (0);
}

void	reset_fd_to_std(int to_dup[2], int svg_fd[2])
{
	if (to_dup[1] != 1)
	{
		close(to_dup[1]);
		dup2(svg_fd[1], 1);
		close(svg_fd[1]);
	}
	if (to_dup[0] != 0)
	{
		close(to_dup[0]);
		close(svg_fd[0]);
	}
}

bool	builtin_handler(char *path, t_command *cmd, char **argv)
{
	int		svg_fd[2];
	int		to_dup[2];
	int		new_pipe[2];

	if ((cmd->type_out == '|' || cmd->pipe == PIPE_YES) && pipe(new_pipe))
		return (false);
	builtin_dup_selector(to_dup, cmd, new_pipe[1], svg_fd);
	dup2(to_dup[1], 1);
	if (cmd->type_in == '|')
		close_two(cmd->pipe_fd);
	builtin_exec(path, cmd, argv);
	cmd->pipe_fd[0] = new_pipe[0];
	cmd->pipe_fd[1] = new_pipe[1];
	reset_fd_to_std(to_dup, svg_fd);
	return (true);
}
