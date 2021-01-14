/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:20:27 by nomoon            #+#    #+#             */
/*   Updated: 2021/01/14 10:35:26 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int		count_argv(char **argv)
{
	int i;

	i = -1;
	while (argv[++i])
		;
	return (i);
}

int		builtin_exec(char *path, t_command *cmd, char **argv)
{
    if (!ft_strcmp(path, "pwd") && count_argv(argv) == 1)
        ft_pwd();
    else if (!ft_strcmp(path, "pwd") && count_argv(argv) > 1)
        ft_putstr_fd("pwd: too many arguments\n", 1);
    if (!ft_strcmp(path, "env"))
        print_env(cmd->env);
    if (!ft_strcmp(path, "export"))
        export_check(cmd->env, argv);
    if (!ft_strcmp(path, "unset"))
        unset(cmd->env, argv);
    if (!ft_strcmp(path, "echo"))
        ft_echo(cmd->env, argv);
    if (!ft_strcmp(path, "cd"))
    {
        
        ft_cd(argv, cmd->env);
    }
    return (1);
}
