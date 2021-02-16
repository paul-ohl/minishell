/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checkers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoon <nomoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 20:05:24 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/16 14:50:59 by nomoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

bool	check_redirect(char *str, int i, int *err)
{
	if (str[i] != '>' && str[i] != '<')
		return (true);
	if (str[i++] == '>' && str[i] == '>')
		i++;
	while (str[i] == ' ')
		i++;
	if (ft_strchr("><;|", str[i]))
		return (set_error_code(err, SYN_ERR_REDIR));
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

bool	check_cmd_separators(char *str, int i, int *err)
{
	char	current_char;

	current_char = str[i];
	if (current_char != '|' && current_char != ';')
		return (set_error_code(err, SYNTAX_CLEAR));
	if (current_char == '|' && str[i + 1] == '|')
		return (set_error_code(err, SYN_NO_SUP_OR));
	i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (set_error_code(err, SYN_ERR_PIPE));
	if (str[i] == ';')
		return (set_error_code(err, SYN_ERR_SEMICOL));
	else if (current_char == '|' && !str[i])
		return (set_error_code(err, SYN_ERR_PIPE));
	return (true);
}

bool	str_check(char *str, int *err)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\\')
		{
			i++;
			if (!str[i])
				return (set_error_code(err, SYN_ERR_BKSL));
		}
		else if (!check_quotes(str, &i))
			return (set_error_code(err, SYN_ERR_QUOT));
		else if (!check_cmd_separators(str, i, err))
			return (false);
		else if (!check_redirect(str, i, err))
			return (false);
		else if (str[i] == '&' && str[i + 1] == '&')
			return (set_error_code(err, SYN_NO_SUP_AND));
	}
	return (true);
}
