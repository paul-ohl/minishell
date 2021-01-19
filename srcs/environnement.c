/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:00:45 by paulohl           #+#    #+#             */
/*   Updated: 2021/01/19 12:07:53 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

char	*get_env_str(char *str, t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (!i)
		return ("$");
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, str, i) && tmp->name[i] == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

char	*get_env(t_command *command, int *i)
{
	char	*env_var;

	if (command->cmd[(*i)++] != '$')
		return ("");
	if (command->cmd[*i] == '?')
		return (ft_itoa(command->return_value));
	env_var = get_env_str(command->cmd + *i, command->env);
	while (ft_isalnum(command->cmd[*i]) || command->cmd[*i] == '_')
		(*i)++;
	(*i)--;
	return (env_var);
}

char	**to_string_array(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	int		i;
	int		name_len;

	tmp = env;
	i = 1;
	if (!tmp)
		i = 0;
	else
		while ((tmp = tmp->next))
			i++;
	tmp = env;
	if (!(envp = malloc(sizeof(envp) * (i + 1))))
		return (NULL);
	envp[i] = 0;
	if (!tmp)
		return (envp);
	i = 0;
	while (tmp)
	{
		if (!(envp[i] = malloc(sizeof(envp[i]) * ft_strlen(tmp->name) + ft_strlen(tmp->value) + 2)))
			return (free_envp(envp, i));
		name_len = ft_strcpy(envp[i], tmp->name);
		envp[i][name_len] = '=';
		ft_strcpy(envp[i] + name_len + 1, tmp->value);
		i++;
		tmp = tmp->next;
	}
	return (envp);
}
