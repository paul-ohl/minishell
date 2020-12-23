# Folders and Names
NAME		= minishell
SRCSDIR		= srcs
OBJSDIR		= objs
INCLUDES	= inc
EXTLIB		= libft

SRCS		= parser.c prompt.c utils.c parse_command.c interpret_string.c \
			  environnement.c free.c error_handler.c get_executable_path.c \
			  execute.c env.c export.c pwd.c execute_builtin.c unset.c echo.c

# Compiler options
CC			= gcc
CFLAGS		= -Wall -Wextra -g3 #-fsanitize=address

###################################################
# The rest is done by the MakeFile automatically, #
# you should not have to modify it				  #
###################################################

OBJS	= $(SRCS:%.c=$(OBJSDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(EXTLIB)/$(EXTLIB).a
	@echo "Assembling $@"
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS): $(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(@D)
	@echo Compiling $<
	@$(CC) $(CFLAGS) -I$(INCLUDES) -I$(EXTLIB) -c $< -o $@

$(EXTLIB)/$(EXTLIB).a:
	@echo "Compiling $@"
	@$(MAKE) -s -C $(EXTLIB)

clean:
	rm -rf $(OBJSDIR)
	@$(MAKE) -s -C $(EXTLIB) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -s -C $(EXTLIB) fclean

re: fclean all

test: all
	./$(NAME)

.PHONY: all clean fclean re test bonus
