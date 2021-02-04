/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:20:27 by nomoon            #+#    #+#             */
/*   Updated: 2021/02/04 14:32:35 by paulohl          ###   ########.fr       */
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
		print_env(cmd->env);
	else if (!ft_strcmp(path, "export"))
		cmd->return_value = export_check(cmd->env, argv);
	else if (!ft_strcmp(path, "unset"))
		cmd->return_value = unset(cmd->env, argv);
	else if (!ft_strcmp(path, "echo"))
		cmd->return_value = ft_echo(argv);
	else if (!ft_strcmp(path, "cd"))
		cmd->return_value = ft_cd(argv, cmd->env);
	else if (!ft_strcmp(path, "exit"))
		ft_exit(cmd->env, cmd, argv);
}

bool	builtin_handler(char *path, t_command *cmd, char **argv)
{
	int		to_dup[2];
	int		svg_fd[2];
	int		new_pipe[2];

	if ((cmd->type_out == '|' || cmd->pipe == PIPE_YES) && pipe(new_pipe))
		return (false);
	dup_selector(to_dup, cmd, new_pipe[1]);
	svg_fd[0] = dup(0);
	svg_fd[1] = dup(1);
	dup2(to_dup[0], 0);
	dup2(to_dup[1], 1);
	if (cmd->type_in == '|')
	{
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
	}
	builtin_exec(path, cmd, argv);
	cmd->pipe_fd[0] = new_pipe[0];
	cmd->pipe_fd[1] = new_pipe[1];
	close(to_dup[0]);
	close(to_dup[1]);
	dup2(svg_fd[0], 0);
	dup2(svg_fd[1], 1);
	close(svg_fd[0]);
	close(svg_fd[1]);
	return (true);
}
