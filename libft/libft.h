/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:39:50 by pohl              #+#    #+#             */
/*   Updated: 2020/11/18 06:31:41 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <strings.h>

typedef struct	s_opt
{
	char	*optarg;
	int		optind;
	int		optopt;
	int		opterr;
	int		optreset;
}				t_opt;

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_strchr(const char *str, char c);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *str, const char *needle, size_t len);
char			*ft_strrchr(const char *str, char c);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_atoi(const char *str);
int				ft_atoi_increment(const char *str, int *i);
void			*ft_memset(void *str, int c, size_t n);
void			ft_bzero(void *str, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t len);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const void *str1, const void *str2, size_t n);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
char			**ft_split(char const *s, char c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				get_next_line(int fd, char **line);
int				is_whitespace(char c);
int				ft_intlen(int nbr);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_getopt(t_opt *options, int argc,
					char *argv[], char *optstring);
size_t			ft_strcpy(char *dst, const char *src);
char			**ft_free_array(char **array);
char			*ft_strndup(char *str, int len);

#endif
