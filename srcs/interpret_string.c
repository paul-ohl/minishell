/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:37:47 by pohl              #+#    #+#             */
/*   Updated: 2021/02/09 15:26:50 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdarg.h>

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
