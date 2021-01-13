/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 08:44:15 by elbouju           #+#    #+#             */
/*   Updated: 2021/01/13 11:09:35 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>
#include "../libft/libft.h"
#include <limits.h>
#include <stdio.h>

int	is_in_env(t_env *env, char *str)
{
    t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->value))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
		return (1);
	if (is_in_env(env, oldpwd) == 0)
		change_value(env, oldpwd);
	// ft_memdel(oldpwd);
	return (0);
}

int	update_pwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (!(pwd = ft_strjoin("PWD=", cwd)))
		return (1);
	if (is_in_env(env, pwd) == 0)
		change_value(env, pwd);
	// ft_memdel(oldpwd);
	return (0);
}

char	*get_oldpwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && tmp->name)
	{
		if (!ft_strcmp("OLDPWD", tmp->name))
		{
			printf("123 = %s\n", tmp->value);
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
