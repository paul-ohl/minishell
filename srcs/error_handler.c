/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:11:39 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/02 19:29:08 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

enum e_error_codes 
{
	SYNTAX_CLEAR = 0,
	SYN_ERR_PIPE,
	SYN_ERR_QUOT,
	SYN_ERR_BKSL,
	SYN_NO_SUP_OR,
	SYN_NO_SUP_AND,
	SYN_ERR_SEMICOL,
	SYN_ERR_REDIR
};

bool	set_error_code(t_command *command, int *error_var, const int error_code)
{
	if (error_code)
		command->return_value = 258;
	*error_var = error_code;
	if (error_code)
		return (false);
	return (true);
}

bool	check_redirect(char *str, int i, int *err, t_command *command)
{
	if (str[i] != '>' && str[i] != '<')
		return (true);
	if (str[i++] == '>' && str[i] == '>')
		i++;
	while (str[i] == ' ')
		i++;
	if (ft_strchr("><;|", str[i]))
		return (set_error_code(command, err, SYN_ERR_REDIR));
	return (true);
}

bool	check_quotes(char *str, int *original_iterator)
{
	char	to_skip;
	int		i;

	i = *original_iterator;
	if ((str[i] == '\'' || str[i] == '"') && !str[i + 1])
		return (false);
	to_skip = str[i];
	i = skip_quote(str, i);
	if (str[i] != to_skip)
		return (false);
	*original_iterator = i;
	return (true);
}

bool	check_cmd_separators(char *str, int i, int *err, t_command *command)
{
	char	current_char;

	current_char = str[i];
	if (current_char != '|' && current_char != ';')
		return (set_error_code(command, err, SYNTAX_CLEAR));
	if (current_char == '|' && str[i + 1] == '|')
		return (set_error_code(command, err, SYN_NO_SUP_OR));
	i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (set_error_code(command, err, SYN_ERR_PIPE));
	if (str[i] == ';')
		return (set_error_code(command, err, SYN_ERR_SEMICOL));
	else if (current_char == '|' && !str[i])
		return (set_error_code(command, err, SYN_ERR_PIPE));
	return (true);
}

bool	str_check(char *str, int *err, t_command *command)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\\')
		{
			i++;
			if (!str[i])
				return (set_error_code(command, err, SYN_ERR_BKSL));
		}
		else if (!check_quotes(str, &i))
			return (set_error_code(command, err, SYN_ERR_QUOT));
		else if (!check_cmd_separators(str, i, err, command))
			return (false);
		else if (!check_redirect(str, i, err, command))
			return (false);
		else if (str[i] == '&' && str[i + 1] == '&')
			return (set_error_code(command, err, SYN_NO_SUP_AND));
	}
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

void	print_parser_error(int err, t_command *command)
{
	ft_putstr_fd("Minishell error: ", 2);
	if (err == 2 && command->return_value)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		command->return_value = 0;
	}
}
