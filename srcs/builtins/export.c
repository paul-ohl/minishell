/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:40:48 by nomoon            #+#    #+#             */
/*   Updated: 2021/02/04 17:17:11 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int	check_name(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '=')
		return (2);
	while (str[++i] && str[i] != '=')
		if (!ft_isalpha(str[i]))
			return (2);
	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (0);
	return (1);
}

int	change_value(t_env *env, char *argv)
{
	t_env	*tmp;
	char	*compared_string;

	tmp = env;
	compared_string = ft_substr(argv, 0, len_env(argv));
	while (tmp->next)
	{
		if (!ft_strcmp(compared_string, tmp->name))
		{
			free(compared_string);
			free(tmp->value);
			tmp->value = ft_substr(argv, len_env(argv) + 1,
					ft_strlen(argv) - len_env(argv) - 1);
			return (0);
		}
		tmp = tmp->next;
	}
	free(compared_string);
	return (1);
}

int	existing_name(t_env *env, char *argv)
{
	t_env	*tmp;
	char	*compared_string;

	tmp = env;
	compared_string = ft_substr(argv, 0, len_env(argv));
	while (tmp->next)
	{
		if (!ft_strcmp(compared_string, tmp->name))
		{
			free(compared_string);
			return (0);
		}
		tmp = tmp->next;
	}
	free(compared_string);
	return (1);
}

int	export_check(t_env *env, char **argv)
{
	int i;
	int	return_value;

	i = 0;
	return_value = 0;
	if (count_argv(argv) == 1)
		export(env, count_argv(argv), argv[i]);
	while (argv[++i])
	{
		if (check_name(argv[i]) == 2)
		{
			printf("bash: export: `%s' : not a valid identifier\n", argv[i]);
			return_value = 1;
		}
		else if (check_name(argv[i]) == 1 || check_name(argv[i]) == 0)
		{
			if (existing_name(env, argv[i]) == 1)
				export(env, count_argv(argv), argv[i]);
			else if (existing_name(env, argv[i]) == 0
				&& check_name(argv[i]) == 0)
				change_value(env, argv[i]);
			return_value = 0;
		}
	}
	return (return_value);
}

int	export(t_env *env, int argc, char *argv)
{
	t_env	*tmp;
	t_env	*temp;

	tmp = env;
	if (argc == 1)
		print_env_alphasort(env);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(temp = malloc(sizeof(t_env))))
			return (0);
		temp->name = tmp->name;
		temp->value = tmp->value;
		tmp->name = ft_substr(argv, 0, len_env(argv));
		tmp->value = ft_substr(argv, len_env(argv) + 1,
				ft_strlen(argv) - len_env(argv) - 1);
		tmp->next = temp;
		temp->next = 0;
	}
	return (1);
}
