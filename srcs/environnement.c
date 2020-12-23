/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:00:45 by paulohl           #+#    #+#             */
/*   Updated: 2020/11/24 10:36:32 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*get_env_str(char *str, char **envp)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (!i)
		return ("$");
	while (envp[j])
	{
		if (!ft_strncmp(envp[j], str, i) && envp[j][i] == '=')
			return (envp[j] + i + 1);
		j++;
	}
	return ("");
}

char	*get_env(t_command *command, int *i, char **envp)
{
	char	*env_var;

	if (command->cmd[(*i)++] != '$')
		return ("");
	if (command->cmd[*i] == '?')
		return (ft_itoa(command->return_value));
	env_var = get_env_str(command->cmd + *i, envp);
	while (ft_isalnum(command->cmd[*i]) || command->cmd[*i] == '_')
		(*i)++;
	(*i)--;
	return (env_var);
}
