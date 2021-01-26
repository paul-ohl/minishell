SRCS		= ft_atoi.c ft_atoi_increment.c ft_bzero.c ft_calloc.c \
				ft_intlen.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
				ft_isdigit.c ft_isprint.c ft_itoa.c ft_strcpy.c \
				ft_memccpy.c ft_memchr.c ft_memcmp.c ft_getopt.c \
				ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
				ft_strchr.c ft_strcmp.c ft_strdup.c ft_strjoin.c \
				ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
				ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
				ft_substr.c ft_tolower.c ft_toupper.c is_whitespace.c \
				ft_free_array.c ft_strndup.c

OBJ_DIR		= objs
SRC_DIR		= srcs
INC_DIR		= .

OBJS		:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

NAME		= libft.a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

all:			$(NAME)

$(NAME):		$(OBJS)
	ar rc $(NAME) $(OBJS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY:	all clean clean re
