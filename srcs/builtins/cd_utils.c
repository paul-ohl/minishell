/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoon <nomoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 08:44:15 by elbouju           #+#    #+#             */
/*   Updated: 2021/02/16 08:35:10 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

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
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (1);
	if (is_in_env(env, oldpwd) == 0)
		change_value(env, oldpwd);
	ft_memdel(oldpwd);
	return (0);
}

int	update_pwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (1);
	if (is_in_env(env, pwd) == 0)
		change_value(env, pwd);
	ft_memdel(pwd);
	return (0);
}

char	*get_oldpwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && tmp->name)
	{
		if (!ft_strcmp("OLDPWD", tmp->name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
