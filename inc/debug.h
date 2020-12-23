/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:40 by paulohl           #+#    #+#             */
/*   Updated: 2020/11/11 08:44:08 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEVELOP_H
# define DEVELOP_H

# define DD(x) printf("%d\n", x)
# define D2D(x, y) printf("%d %d\n", x, y)
# define D3D(x, y, z) printf("%d %d %d\n", x, y, z)
# define DS(x) printf("%s\n", x)
# define D2S(x, y) printf("%s %s\n", x, y)
# define D3S(x, y, z) printf("%s %s %s\n", x, y, z)
# define DP(x) printf("%p\n", x)
# define D2P(x, y) printf("%p %p\n", x, y)
# define D3P(x, y, z) printf("%p %p %p\n", x, y, z)

# include <stdio.h>
# include <sys/errno.h>
# include <unistd.h>

#endif
