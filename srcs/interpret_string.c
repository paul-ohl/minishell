/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:37:47 by pohl              #+#    #+#             */
/*   Updated: 2021/02/02 19:16:32 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdarg.h>

int	env_len(t_command *command, int *start)
{
	int		env_variable_len;
	char	*env_var;

	env_var = get_env(command, start);
	env_variable_len = ft_strlen(env_var) - 1;
	if (command->cmd[*start] == '?')
		free(env_var);
	return (env_variable_len);
}

int	fill_single_quotes(char *input, char *output, int *i)
{
	int		tmp;
	int		return_value;

	tmp = skip_quote(input, *i);
	output = ft_memcpy(output, input + *i + 1, tmp - *i - 1);
	return_value = tmp - *i - 1;
	*i = tmp;
	return (return_value);
}

void	fill_str(char *output, t_command *command, int *start_end)
{
	int		i;
	int		inside_quotes;

	i = start_end[0] - 1;
	inside_quotes = 0;
	while (++i < start_end[1] && command->cmd[i])
	{
		if (command->cmd[i] == '\\' && (i++) != -1)
			*(output++) = command->cmd[i];
		else if (command->cmd[i] == '\'' && !inside_quotes)
			output += fill_single_quotes(command->cmd, output, &i);
		else if (command->cmd[i] == '$')
			output += ft_strcpy_free_input(output, get_env(command, &i),
					(command->cmd[i] == '?'));
		else if (command->cmd[i] == '~' && !inside_quotes)
			output += ft_strcpy(output, get_env_str("HOME", command->env));
		else if (command->cmd[i] == '"')
			inside_quotes = !inside_quotes;
		else
			*(output++) = command->cmd[i];
	}
}

int	get_processed_len(t_command *command, int start, int end)
{
	int		processed_len;
	int		tmp;
	int		inside_quotes;

	processed_len = 0;
	inside_quotes = 0;
	while (start < end && command->cmd[start])
	{
		if (command->cmd[start] == '\'' && !inside_quotes
			&& (tmp = skip_quote(command->cmd, start))
			&& command->cmd[tmp] == '\''
			&& (processed_len += tmp - start - 2) != -7)
			start = tmp;
		else if (command->cmd[start] == '"' && (processed_len--) != -42)
			inside_quotes = !inside_quotes;
		else if (command->cmd[start] == '\\' && start < end - 1)
			start++;
		else if (command->cmd[start] == '$')
			processed_len += env_len(command, &start);
		else if (command->cmd[start] == '~')
			processed_len += ft_strlen(get_env_str("HOME", command->env)) - 1;
		start++;
		processed_len++;
	}
	return (processed_len);
}

char	*get_word(t_command *command, int start, int end)
{
	char	*result_str;
	int		result_len;
	int		start_end[2];

	if (command->cmd[start] == ' ')
		start++;
	result_len = get_processed_len(command, start, end);
	result_str = malloc(sizeof(result_str) * (result_len + 1));
	if (!result_str)
		return (NULL);
	result_str[result_len] = 0;
	if (!result_len)
		return (result_str);
	start_end[0] = start;
	start_end[1] = end;
	fill_str(result_str, command, start_end);
	return (result_str);
}
