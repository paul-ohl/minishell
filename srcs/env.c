/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoon <nomoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:45:33 by nomoon            #+#    #+#             */
/*   Updated: 2020/12/19 13:35:51 by nomoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../inc/minishell.h"
#include "../libft/libft.h"

int		len_env(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

// void sort_alpha(t_file **begin_list)
// {
//   t_file    *list;
//   char  *tmp;
//   list = *begin_list;
//   if (list)
//     {
//         while (list && list->next)
//         {
//             if (strcmp(list->file_name, list->next->file_name) > 0)
//             {
//                 tmp = list->file_name;
//                 list->file_name = list->next->file_name;
//                 list->next->file_name = tmp;
//                 counter = counter + 1;
//                 printf("swap=%d\n",counter);
//             }
//         list = list->next;
//         }
//     }
// }

void	print_env_alhasort(t_env *env)
{
	t_env   *tmp;
	t_env   *beginning;
	char    *tempname;
	char    *tempval;
	int     total;
	t_env   *beg;
	total = 0;
	tmp = env;
	beginning = tmp;
	beg = tmp;
	while (tmp)
	{
		tmp->sort = total;
		total += 1;
		tmp = tmp->next;
	}
	tmp = beginning;
	printf("TOTAL %d\n", total);
	while (beginning && beginning->next)
	{
		while (tmp && tmp->next && ft_strcmp(tmp->name, tmp->next->name) > 0)
		{
			tmp->sort += 1;
			tmp->next->sort -= 1;
			// tempname = tmp->name;
			// tempval = tmp->value;
			// tmp->name = tmp->next->name;
			// tmp->value = tmp->next->value;
			// tmp->next->value = tempval;
			// tmp->next->name = tempname;
			tmp = tmp->next;
			printf("1\n");
		}
		printf("blabla\n");
		beginning = beginning->next;
		tmp = beginning;
	}
			// else if (ind == 1)
		// {
			// ft_putstr_fd(tmp->name, 1);
			// ft_putstr_fd("=", 1);
			// ft_putstr_fd(tmp->value, 1);
			// write(1, "\n", 1);
		// }
	printf("tu connais\n");
	print_env(beg, 1);
}

void	print_env(t_env *env, int ind)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		// printf("%d && %d\n", tmp->aff, ind);
		if (tmp->aff == 0)
		{
			printf("\nnb %d\n", tmp->sort);
			ft_putstr_fd(tmp->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->value, 1);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}

t_env	*stock_env(t_env *env, char **envp)
{
	int     i;
	t_env   *tmp;
	t_env   *new;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	tmp = env;
	env->name = ft_substr(envp[0], 0, len_env(envp[0]));
	env->value = ft_substr(envp[0], len_env(envp[0]) + 1,
	ft_strlen(envp[0]) - len_env(envp[0]) - 1);
	i = 0;
	while (envp[++i])
	{
		if (!(new = malloc(sizeof(t_env))))
			return (NULL);
		new->name = ft_substr(envp[i], 0, len_env(envp[i]));
		new->value = ft_substr(envp[i], len_env(envp[i]) + 1,
		ft_strlen(envp[i]) - len_env(envp[i]) - 1);
		new->next = NULL;
		env->next = new;
		env = env->next;
	}
	env->next = NULL;
	return (tmp);
}
