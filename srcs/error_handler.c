/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:11:39 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/02 11:41:53 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#define SYNTAX_CLEAR 0
#define SYN_ERR_PIPE 1
#define SYN_ERR_QUOT 2
#define SYN_ERR_BKSL 3
#define SYN_NO_SUP_OR 4
#define SYN_NO_SUP_AND 5
#define SYN_ERR_SEMICOL 6
#define SYN_ERR_REDIR 7

int	check_redirect(char *str, int i, int *err)
{
	if (str[i] != '>' && str[i] != '<')
		return (*err = SYNTAX_CLEAR);
	if (str[i++] == '>' && str[i] == '>')
		i++;
	while (str[i] == ' ')
		i++;
	if (ft_strchr("><;|", str[i]))
		return (*err = SYN_ERR_REDIR);
	return (*err = SYNTAX_CLEAR);
}

int	check_quotes(char *str, int i)
{
	char	to_skip;

	if ((str[i] == '\'' || str[i] == '"') && !str[i + 1])
		return (-1);
	to_skip = str[i];
	i = skip_quote(str, i);
	if (str[i] != to_skip)
		return (-1);
	else
		return (i);
}

int	check_cmd_separators(char *str, int i, int *err)
{
	char	current_char;

	current_char = str[i];
	if (current_char != '|' && current_char != ';')
		return (*err = SYNTAX_CLEAR);
	if (current_char == '|' && str[i + 1] == '|')
		return (*err = SYN_NO_SUP_OR);
	i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (*err = SYN_ERR_PIPE);
	if (str[i] == ';')
		return (*err = SYN_ERR_SEMICOL);
	else if (current_char == '|' && !str[i])
		return (*err = SYN_ERR_PIPE);
	return (*err = SYNTAX_CLEAR);
}

int	basic_syntax_check(char *str, int *err)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		str++;
	if (str[i] == '|')
		return (*err = SYN_ERR_PIPE);
	if (str[i] == ';')
		return (*err = SYN_ERR_SEMICOL);
	i--;
	while (str[++i])
	{
		if (str[i] == '\\' && !str[i + 1])
			return (*err = SYN_ERR_BKSL);
		else if (str[i] == '\\')
			i++;
		else if ((i = check_quotes(str, i)) == -1)
			return (*err = SYN_ERR_QUOT);
		else if (check_cmd_separators(str, i, err)
			|| check_redirect(str, i, err))
			return (*err);
		else if (str[i] == '&' && str[i + 1] == '&')
			return (*err = SYN_NO_SUP_AND);
	}
	return (*err = SYNTAX_CLEAR);
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
