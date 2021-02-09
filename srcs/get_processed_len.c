/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_processed_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:24:16 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/09 15:26:34 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

int	get_sq_len(char *cmd, int *start, int inside_quotes)
{
	int	tmp;
	int	singlequotes_len;

	if (inside_quotes)
		return (0);
	tmp = skip_quote(cmd, *start);
	if (cmd[tmp] != '\'')
		return (0);
	singlequotes_len = tmp - *start - 2;
	*start = tmp;
	return (singlequotes_len);
}

int	get_processed_len(t_command *command, int start, int end)
{
	int		processed_len;
	int		inside_quotes;

	processed_len = 0;
	inside_quotes = 0;
	while (start < end && command->cmd[start])
	{
		if (command->cmd[start] == '\'')
			processed_len += get_sq_len(command->cmd, &start, inside_quotes);
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
