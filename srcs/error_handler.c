/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:11:39 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/07 20:13:05 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

bool	set_error_code(t_command *command, int *error_var, const int error_code)
{
	if (error_code)
		command->return_value = 258;
	*error_var = error_code;
	if (error_code)
		return (false);
	return (true);
}

bool	syntax_check(char *str, int *err, t_command *command)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		str++;
	if (str[i] == '|')
		return (set_error_code(command, err, SYN_ERR_PIPE));
	if (str[i] == ';')
		return (set_error_code(command, err, SYN_ERR_SEMICOL));
	if (!str_check(str + i, err, command))
		return (false);
	return (set_error_code(command, err, SYNTAX_CLEAR));
}

void	print_syntax_error(int err)
{
	ft_putstr_fd("Minishell error: ", 2);
	if (err == SYN_ERR_QUOT)
		ft_putstr_fd("Unclosed quotes in the command.\n", 2);
	else if (err == SYN_ERR_PIPE)
		ft_putstr_fd("Pipe error.\n", 2);
	else if (err == SYN_ERR_SEMICOL)
		ft_putstr_fd("Semicolon error.\n", 2);
	else if (err == SYN_ERR_BKSL)
		ft_putstr_fd("Backslash at the end of the string.\n", 2);
	else if (err == SYN_NO_SUP_OR)
		ft_putstr_fd("'||' is not supported in minishell.\n", 2);
	else if (err == SYN_NO_SUP_AND)
		ft_putstr_fd("'&&' is not supported in minishell.\n", 2);
	else if (err == SYN_ERR_REDIR)
		ft_putstr_fd("Incorrect redirection.\n", 2);
	else
		ft_putstr_fd("Error code unknown.\n", 2);
}
