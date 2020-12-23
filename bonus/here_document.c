/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 10:28:00 by paulohl           #+#    #+#             */
/*   Updated: 2020/11/30 11:17:53 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int		here_doc_handler(char *stop)
{
	int		here_doc[2];
	char	buffer[1000];
	int		tmp;

	if (pipe(here_doc))
		return (0);
	buffer[0] = 0;
	tmp = 0;
	while (tmp != -1)
	{
		write(1, "> ", 2);
		tmp = read(0, buffer, 999);
		buffer[tmp - 1] = 0;
		if (ft_strcmp(stop, buffer))
		{
			buffer[tmp - 1] = '\n';
			write(here_doc[1], buffer, tmp);
		}
		else
			tmp = -1;
	}
	write(here_doc[1], "\0", 1);
	close(here_doc[1]);
	return (here_doc[0]);
}

int		main(int argc, char **argv)
{
	int		tmp;
	int		doc;
	char	buffer[1000];

	if (argc != 2)
		return (12);
	doc = here_doc_handler(argv[1]);
	tmp = read(doc, buffer, 999);
	buffer[tmp] = 0;
	printf("Result:\n%s", buffer);
}
