/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:29 by paulohl           #+#    #+#             */
/*   Updated: 2021/01/10 17:17:03 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_CMD_LEN 262144
# define PIPE_YES 'y'
# define PIPE_NO 'n'
# define GLOB_SUCCESS 0
# define GLOB_ERR_MALLOC 1
# define GLOB_CMD_LEN 2

# include "debug.h"

/*
** s_command is the structure containing information about each issued command.
** cmd contains the raw command to be interpreted by parse_command,
** pipe is set to PIPE_YES whenever there is a '|' at the end of the command,
** type_in and type_out are a character indicating the type of redirection :
** ';' (no redirection), '|', '<', '>' or 'a' ('>>'),
** fd_in and fd_out contain the file descriptor to write to.
** return_value is a variable set to the return value of each launched command,
** it is set to errno when an error is encountered.
*/

typedef struct			s_env {
	char				*name;
	char				*value;
	int					aff;
	int					sort;
	struct				s_env *next;
}						t_env;

typedef struct			s_command {
	char				*cmd;
	char				pipe;
	char				type_in;
	char				type_out;
	int					fd_in;
	int					fd_out;
	int					return_value;
	int					pipe_fd[2];
	t_env				*env;
}						t_command;

int						parser(char *buffer, t_command *command);
int						skip_quote(char *buffer, int i);
int						skip_redirect(char *buffer, int i);
char					**parse_command(t_command *cmd, int argc);
char					*get_word(t_command *cmd, int st, int end);
char					*get_env(t_command *cmd, int *i);
char					**free_argv(char **argv, int argc, char *exec_path);
int						basic_syntax_check(char *str);
void					print_syntax_error(int err);
void					print_parser_error(int err, t_command *command);
t_command				*init_struct(char **envp);
void					set_redirect(t_command *command, char type, int fd);
void					reset_fds(t_command *command);
char					*get_executable_path(char *program_name, t_env *env);
int						execute(char *executable_path, t_command *cmd, char **argv);
char					*get_env_str(char *str, t_env *env);
int						ft_strcpy_free_input(char *dst, char *src, int to_free);
int						is_builtin(char *path);
t_env					*stock_env(char **envp);
void    				print_env(t_env *env, int ind);
int     				len_env(char *str);
int     				count_argv(char **argv);
int     				export(t_env *env, int argc, char *argv);
int						ft_pwd(void);
int						builtin_exec(char *path, t_command *cmd, char **argv);
int     				unset(t_env *env, char **argv);
void					print_env_alhasort(t_env *env);
int						ft_echo(char **args);
int						export_check(t_env *env, char **argv);
char					**to_string_array(t_env *env);
char					**free_envp(char **envp, int end);

#endif
