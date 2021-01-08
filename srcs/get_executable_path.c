/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_executable_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoon <nomoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:19:52 by paulohl           #+#    #+#             */
/*   Updated: 2020/12/23 15:25:01 by nomoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "minishell.h"

char	*ft_concat(char *str1, char *str2, char separator)
{
	int		i;
	int		j;
	char	*result;

	if (!str1 || !str2)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i])
		i++;
	while (str2[j])
		j++;
	if (!(result = malloc(sizeof(result) * (i + j + 2))))
		return (NULL);
	i = -1;
	while (str1[++i])
		result[i] = str1[i];
	result[i++] = separator;
	j = -1;
	while (str2[++j])
		result[i + j] = str2[j];
	result[i + j] = 0;
	return (result);
}

int		is_builtin(char *path)
{
	if (!ft_strcmp(path, "exit"))
		return (1);
	if (!ft_strcmp(path, "export"))
		return (1);
	if (!ft_strcmp(path, "unset"))
		return (1);
	if (!ft_strcmp(path, "env"))
		return (1);
	if (!ft_strcmp(path, "cd"))
		return (1);
	if (!ft_strcmp(path, "pwd"))
		return (1);
	if (!ft_strcmp(path, "echo"))
		return (1);
	return (0);
}

int		is_file_executable(char *path)
{
	struct stat	buffer;

	if (!ft_strchr("./", path[0]))
		return (0);
	return (stat(path, &buffer) == 0);
}

char	*get_executable_path(char *program_name, t_env *env)
{
	char		**path;
	char		*program;
	int			i;

	if (is_builtin(program_name) || is_file_executable(program_name))
		return (ft_strdup(program_name));
	if (!(path = ft_split(get_env_str("PATH", env), ':')))
		return (NULL);
	i = 0;
	while (path[i])
	{
		program = ft_concat(path[i], program_name, '/');
		if (is_file_executable(program))
		{
			ft_free_array(path);
			return (program);
		}
		free(program);
		i++;
	}
	ft_free_array(path);
	return (NULL);
}
