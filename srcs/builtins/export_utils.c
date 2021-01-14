/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbouju <elbouju@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 08:45:28 by elbouju           #+#    #+#             */
/*   Updated: 2021/01/14 10:22:24 by elbouju          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../inc/minishell.h"
#include "../libft/libft.h"

char    *ft_strjoin_free(char *s1, char *s2, char state)
{
	char    *str;
	size_t  len_s1;
	size_t  len_s2;

	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(str = ft_calloc(len_s1 + len_s2 + 2, sizeof(char))))
		return (NULL);
	ft_memcpy(str, s1, len_s1 + 1);
	ft_memcpy(str + len_s1, s2, len_s2);
	state == 1 || state == 3 ? free(s1) : 0;
	state == 2 || state == 3 ? free(s2) : 0;
	return (str);
}

void    export_print(char **tab)
{
    int i;

    i = -1;
    while (tab[++i])
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(ft_substr(tab[i], 0, len_env(tab[i])), 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd("\"", 1);
        ft_putstr_fd(ft_substr(tab[i], len_env(tab[i]) + 1,
			ft_strlen(tab[i]) - len_env(tab[i]) - 1), 1);
        ft_putstr_fd("\"", 1);
        write(1, "\n", 1);
    }
}

void    sort_tab(char **tab, int total)
{
    int     i;
    char    *tmp;
    
    i = -1;
    while (total != 0)
    {
        i = -1;
        while (tab[++i] && tab[i + 1] && i < total)
        {
            if (ft_strcmp(tab[i], tab[i + 1]) > 0)
            {
                tmp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = tmp;
            }
        }
        total--;
    }
    i = -1;
    export_print(tab);
    free(tab);
}

int env_size(t_env *env)
{
    t_env   *tmp;
    int     i;

    i = 0;
    tmp = env;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}

int print_env_alphasort(t_env *env)
{
    t_env   *tmp;
    char    **tab;
    char    *tmp1;
    int     i;

    i = -1;
    tmp = env;
    if (!(tab = ft_calloc(sizeof(char*), (env_size(env) + 1))))
        return (0);
    tmp = env;
    while (tmp)
    {
        tmp1 = ft_strjoin(tmp->name, "=");
        tmp1 = ft_strjoin_free(tmp1, tmp->value, 1);
        tab[++i] = tmp1;
        tmp = tmp->next;
    }
    sort_tab(tab, env_size(env));
}