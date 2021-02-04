/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:25:31 by nomoon            #+#    #+#             */
/*   Updated: 2021/02/02 14:59:33 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>
#include "../libft/libft.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	t_env	*tmp;

	tmp = env;
	while (tmp && tmp->next)
	{
		if (!ft_strncmp(tmp->name, var, len))
		{
			if (!(oldpwd = malloc(sizeof(char) * ft_strlen(tmp->value) + 1)))
				return (NULL);
			oldpwd = tmp->value;
			oldpwd[ft_strlen(tmp->value)] = '\0';
			return (oldpwd);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static int	go_to_patho1(char *env_path, t_env *env)
{
	int ret;
	
	ret = chdir(env_path);
	update_pwd(env);
	return (ret);
}

static int	go_to_path(int option, t_env *env)
{
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", 2);
		if (!env_path)
			return (1);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
		if (!env_path)
			return (1);
		update_oldpwd(env);
	}
	return(go_to_patho1(env_path, env));
}

int	ft_cd(char **args, t_env *env)
{
	int		cd_ret;
	char	*temp;

	if (!args[1])
		return (go_to_path(0, env));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		temp = ft_strdup(get_oldpwd(env));
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		update_pwd(env);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
		{
			if (temp != NULL)
				change_value(env, ft_strjoin("OLDPWD=", temp));
			free(temp);
			print_error(args);
		}
	}
	return (cd_ret);
}
