/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoon <nomoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 19:39:29 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/18 18:22:48 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# define MAX_CMD_LEN 262144
# define PIPE_YES 'y'
# define PIPE_NO 'n'
# define GLOB_SUCCESS 0
# define GLOB_ERR_MALLOC 1
# define GLOB_CMD_LEN 2

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

pid_t	g_fg_proc;
int		g_last_return;

enum e_error_codes
{
	SYNTAX_CLEAR = 0,
	SYN_ERR_PIPE,
	SYN_ERR_QUOT,
	SYN_ERR_BKSL,
	SYN_NO_SUP_OR,
	SYN_NO_SUP_AND,
	SYN_ERR_SEMICOL,
	SYN_ERR_REDIR
};

typedef struct s_env {
	char			*name;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_command {
	char	*cmd;
	char	pipe;
	char	type_in;
	char	type_out;
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	t_env	*env;
}t_command;

bool		parser(char *buffer, t_command *command);
int			skip_quote(char *buffer, int i);
int			skip_redirect(char *buffer, int i);
char		**parse_command(t_command *cmd, int argc);
char		*get_word(t_command *cmd, int st, int end);
char		*get_env(t_command *cmd, int *i);
char		**free_argv(char **argv, int argc, char *exec_path);
bool		syntax_check(char *str, int *err);
void		print_syntax_error(int err);
int			init_struct(char **envp, t_command **command);
void		set_redirect_fd(t_command *command, char type, int fd);
void		reset_fds(t_command *command);
char		*get_executable_path(char *program_name, t_env *env);
bool		execute(char *executable_path, t_command *cmd, char **argv);
char		*get_env_str(char *str, t_env *env);
int			ft_strcpy_free_input(char *dst, char *src, int to_free);
int			is_builtin(char *path);
t_env		*stock_env(char **envp);
int			print_env(t_env *env, char **argv);
int			len_env(char *str);
int			count_argv(char **argv);
int			export(t_env *env, int argc, char *argv);
int			ft_pwd(t_env *env, char **argv);
void		builtin_exec(char *path, t_command *cmd, char **argv);
int			unset(t_env *env, char **argv);
int			print_env_alphasort(t_env *env);
int			ft_echo(char **args);
int			export_check(t_env *env, char **argv);
char		**to_string_array(t_env *env);
char		**free_envp(char **envp, int end);
int			is_in_env(t_env *env, char *str);
char		*get_oldpwd(t_env *env);
int			update_oldpwd(t_env *env);
int			update_pwd(t_env *env);
int			ft_cd(char **args, t_env *env);
int			change_value(t_env *env, char *argv);
int			existing_name(t_env *env, char *argv);
bool		builtin_handler(char *path, t_command *cmd, char **argv);
void		dup_selector(int to_dup[2], t_command *command, int new_pipe_out);
void		sigint_handler(int signal);
void		sigquit_handler(int signal);
t_command	*singleton(void);
void		ft_exit(t_env *env, char **argv);
void		reinit_struct(t_command *command);
char		*ft_strjoin_free(char *s1, char *s2, char state);
bool		set_error_code(int *error_var, const int err_code);
bool		str_check(char *str, int *err);
void		print_redirection_error(char *redirection);
bool		handle_redirection(t_command *command, int *i, int *start);
void		close_two(int fd[2]);
int			get_processed_len(t_command *command, int start, int end);
int			skip_initial_whitespaces_or_redir(char *str);
int			arg_count(char *str);
int			get_user_input(char **line);
void		reinit_struct(t_command *command);
bool		reset_counter(int *i, bool return_value);

#endif
