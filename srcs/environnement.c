/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:00:45 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/07 19:51:49 by paulohl          ###   ########.fr       */
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

int	struct_len(t_env *env)
{
	size_t	i;

	i = 0;
	if (!env)
		return (0);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**to_string_array(t_env *env)
{
	char	**envp;
	int		i;
	int		name_len;

	i = struct_len(env);
	envp = malloc(sizeof(*envp) * (i + 1));
	if (!envp)
		return (NULL);
	envp[i] = 0;
	if (!env)
		return (envp);
	i = 0;
	while (env)
	{
		envp[i] = malloc(sizeof(envp[i])
				* ft_strlen(env->name) + ft_strlen(env->value) + 2);
		if (!envp[i])
			return (free_envp(envp, i));
		name_len = ft_strcpy(envp[i], env->name);
		envp[i][name_len] = '=';
		ft_strcpy(envp[i] + name_len + 1, env->value);
		i++;
		env = env->next;
	}
	return (envp);
}
