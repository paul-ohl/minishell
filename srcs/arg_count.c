/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:49:41 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/09 15:50:28 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	skip_initial_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

/*
** arg_count counts the number of arguments in a command.
*/

int	arg_count(char *str)
{
	int		i;
	int		count;

	i = 0;
	str += skip_initial_whitespaces(str);
	if (!str[i])
		return (0);
	count = 1;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			i = skip_redirect(str, i);
			while (str[i] && str[i + 1] == ' ')
				i++;
		}
		if (str[i] == ' ' && !ft_strchr("<> ", str[i + 1]))
			count++;
		i = skip_quote(str, i);
		if (str[i] == '\\' && str[i + 1])
			i++;
		if (str[i])
			i++;
	}
	return (count);
}
