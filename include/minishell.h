/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 01:20:42 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 17:03:52 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stddef.h>

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/ft_printf_fd.h"

# define ECHO_CMD "echo"
# define EXIT_CMD "exit"
# define CD_CMD "cd"
# define PWD_CMD "pwd"
# define ENV_CMD "env"
# define EXPORT_CMD "export"
# define UNSET_CMD "unset"

# define T_WORD 1
# define T_REDIRECT 2
# define T_PIPE 3
# define T_SEP 4
# define T_NEWLINE 5
# define T_ENV 6
# define T_AND 7
# define T_OR 8
# define T_PAR_OPEN 9
# define T_PAR_CLOSE 10

int	g_exit_status;

# define TRUE 1
# define FALSE 0

# define IN_MINI  10
# define IN_CMD  20
# define IN_HERE_DOC  30
# define OFF_HERE_DOC  40
# define CTRL_C_ON_HEREDOC 1
# define CTRL_C  130

typedef struct s_env
{
	char			*key;
	char			*value;
	int				tmp;
	int				sign;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			*bin;
	struct s_token	*args;
	int				scope;
	int				forked;
	char			**args_array;
	int				in;
	int				out;
	int				pipe[2];
	int				type;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char				*word;
	int					type;
	struct s_token		*prev;
	struct s_token		*next;
}					t_token;

typedef struct s_qoutes_helper
{
	int				j;
	int				k;
	int				*i;
	int				env;
	char			*tmp;
	char			*dest;
}					t_parsing_q;

typedef struct s_minishell
{
	char			*name;
	char			*curdir;
	int				exit;
	char			*line_buf;
	int				quit;
	int				quit2;
	int				*fpip;
	int				*spip;
	int				count;
	int				scope_p;
	int				forked;
	int				count_cmds;
	char			*exit_str;
	struct s_cmd	*cmd_list;
	t_env			*env_list;
	t_env			*env_sorted_list;
	struct s_token	*token_list;
	char			**env_array;
	char			**env_array_local;
	char			**bin;
	t_parsing_q		*q;
}					t_minishell;

void		initialize_minishell(t_minishell *minishell, char **envp);

//****************************** Environment ***************************//

void		env_init(t_minishell *minishell, char **env);
char		*getenv_value(t_minishell *shell, char *key, t_env *env_list);
void		env_cmd_export(t_env **begin);
int			modify_env_list(t_minishell *minishell, char **split, \
				int ex, int join);
void		init_env_list(t_minishell *minishell, char **envp);
void		add_env_entry(t_minishell *minishell, char **envp, \
				int i, t_env **env_list);
t_env		*env_new(char *key, char *value, int flag);
void		insert_sorted_env_node(t_env **env_list, t_env *new_node);
int			env_update_entry(t_env **env_head, t_env *new_node);
void		set_env(t_minishell *minishell, char *env_key, char *value);
int			env_valid_character(char *str);
int			ft_envlen(t_minishell *minishell, char *src, int i);
char		**env_to_array(t_minishell *minishell);
int			ft_env_lstsize(t_env *lst);
t_env		*ft_env_lstlast(t_env *lst);
void		ft_env_lstadd_back(t_env **lst, t_env *new);

//******************************** Parsing *****************************//

int			init_valid_line(char **line, t_minishell *shell);
int			is_whitespace_string(char *str);
int			is_escaped(char *s, int pos);
int			is_only_ascii(char *str);
int			ft_iswhitespace(char c);
int			validate_command(char *buf, t_minishell *shell);
int			contains_unbalanced_quotes(char *buf, t_minishell *shell);
int			validate_syntax(char *line_buf, t_minishell *shell);
int			check_invalid_pipe_syntax(char **ps, char *es, int *exit_status);
int			validate_pipe(char **ps, char *es, int *exit_status);
int			find_token(char **ps, char *es, char *tokens);
int			get_next_token(char **ps, char *es, char **q, char **eq);
int			validate_redirection(char **ps, char *es, int *exit_status);
void		parse_bin(t_minishell *minishell);
int			is_char_str(char c, char *str);
int			in_bracket(char *s, int pos);
int			is_valid_env(char *str);
void		parse_tokens(t_minishell *minishell, t_token **tmp);

// ******************Parsing Line Prompt into Tokens**********************//

void		start_parse(t_minishell *minishell, char *str);
void		split_tokens(t_minishell *minishell, char *str);
int			split_utils(int i, char *str, char *splt, int sign);
int			in_bracket(char *s, int pos);
int			is_escaped(char *s, int pos);
t_token		*create_token(t_minishell *minishell, int i);
t_token		*create_arg_token(t_minishell *minishell, char *word, int type);
int			split_tokens2(t_minishell *minishell, char *str, int *i, \
			t_token **begin);
int			check_error(t_token *token);
char		*iter_tokens(t_minishell *minishell);

//******************Parsing Tokens for Command Chunks************************//

void		parse_tokens(t_minishell *minishell, t_token **tmp);
int			parse_tokens2(t_minishell *shell, t_token **tmp, t_cmd *cmd);
void		add_cmd_list(t_minishell *shell, t_cmd **begin, t_cmd *new);
char		**args_to_array(t_minishell *minishell, t_cmd *cmd);
void		clear_cmd_list(t_cmd **begin, void (*del)(void *));
void		clear_cmd_node_free(t_cmd *cmd);

//****************************** Bin **************************************//

void		parse_bin(t_minishell *minishell);
char		*get_bin(t_minishell *minishell, char *cmd);
int			ft_quotelen(t_minishell *minishell, char *src, int type, int env);
char		*simple_qoutes(t_minishell *minishell, char *src, int *i);
char		*double_quotes(t_minishell *minishell, char *src, int *i, int env);
char		*no_quotes(t_minishell *minishell, char *src, int *i, int env);
char		*handle_quotes(t_minishell *minishell, char *src, int env);
void		next_bracket(t_minishell *minishell);
char		*replace_env2(t_minishell *minishell, char *str, int *i);
char		*replace_env(t_minishell *minishell, char *str, int i);
int			cmd_list_size(t_cmd **begin);

//****************************** Execution *******************************//

int			read_and_execute(const char *prompt, t_minishell *shell);
void		exec_child(t_minishell *minishell, t_cmd *cmd, \
				int fpip[2], int spip[2]);
void		exec(t_minishell *minishell, t_cmd *tmp, int *fpip, int *spip);
void		exeve_checker(t_minishell *minishell, t_cmd *tmp, \
				int *fpip, int *spip);
void		exec_prog(t_minishell *minishell, t_cmd *cmd, \
				int fpip[2], int spip[2]);
void		exec_prog2(t_minishell *minishell, t_cmd *tmp, \
				pid_t pid, int fpip[2]);
void		handle_fd(t_cmd *tmp, int fpip[2], int spip[2]);
void		exec_commands(t_minishell *minishell);
void		exec_commands2(t_minishell *minishell, t_cmd *tmp, int fpipe[2]);
int			count_slash(char *s);
int			ft_strmatch(char *s1, char *s2, int i, int j);
void		save_child_pid(int pid, t_minishell *shell);
int			process_args(t_minishell *minishell, t_cmd *cmd);
void		process_args_env(t_minishell *minishell, t_cmd *cmd);
char		**join_args(t_minishell *minishell, t_cmd *cmd);
void		ft_heredoc(t_minishell *shell, t_token **token, t_cmd *cmd);

//***************************** Siganls *********************************//

void		setup_signals_bash(t_minishell *minishell);
void		set_signal_handler_heredoc(t_minishell *shell);
void		set_signals_exec(void);

//***************************** Redirection *********************************//

void		create_redirect(t_minishell *minishell, t_cmd *cmd);
int			create_redirect2(t_minishell *minishell, t_cmd *cmd, \
				t_token **args, int flags);
t_token		*remove_redirect(t_token *args, t_token **begin);
t_token		*remove_redirect(t_token *args, t_token **begin);
int			find_heredoc(t_minishell *minishell);

//******************************** Builtins *****************************//

void		echo_cmd(t_minishell *minishell, t_cmd *cmd);
void		env_cmd(t_minishell *shell, t_env **begin);
void		pwd_cmd(t_minishell *minishell);
void		cd_cmd(t_minishell *minishell, t_cmd *cmd);
void		export_cmd(t_minishell *minishell, t_cmd *cmd, int forked);
void		unset_cmd(t_minishell *minishell, t_cmd *cmd);
void		exit_cmd(char **argv, t_minishell *shell, int fpipe[2]);
void		edit_pwd(t_minishell *minishell, t_cmd *cmd);

//****************************** Free and Close **************************//

void		free_env_var_list(t_env **env_list);
void		free_env_node(t_env **node);
void		free_and_exit(t_minishell *minishell, int exit_value);
void		free_child(t_minishell *minishell, int exit_num);
void		free_heredoc(t_minishell *minishell, int exit_num);
void		clear_cmd_list_free(t_cmd *cmd);
void		clear_token_list(t_token **begin);
void		free_env2(void *lst);
void		handle_errno(t_minishell *minishell, char *cmd, int type);
void		free_redirect(t_token *tmp);
void		clear_cmd_list(t_cmd **begin, void (*del)(void *));
void		clear_cmd_list_child(t_cmd **begin, void (*del)(void *));
void		clear_cmd_node_free_child(t_cmd *cmd);
void		free_clean(t_minishell *minishell);
void		unlink_file(void);
void		free_panic_exit(t_minishell *minishell, \
				char *error, int exit_status);
void		close_fds(int fpip[2], int spip[2]);

//****************************** Utils ************************************//

t_token		*token_split_to_list(t_minishell *shell, char **split);
void		add_more_args(t_minishell *minishell, t_cmd *cmd, char **split);
char		*supp_newline(t_minishell *minishell, char *src);
char		*iter_tokens(t_minishell *minishell);
void		clear_cmd_list(t_cmd **begin, void (*del)(void *));
void		add_token_list(t_token **begin, t_token *new);
int			token_list_size(t_token **begin);
t_token		*create_token(t_minishell *minishell, int i);
void		add_token_front(t_token **begin, t_token *new);
void		add_cmd_list(t_minishell *shell, t_cmd **begin, t_cmd *new);
void		split_tokens(t_minishell *minishell, char *str);

#endif
