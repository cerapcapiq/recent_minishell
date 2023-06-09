/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:39:31 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/07 17:03:39 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <sys/stat.h>

# define BUILTIN 1
# define CMD 2
# define ARG 3
# define INPUT 4
# define HEREDOC 5
# define TRUNC 6
# define APPEND 7
# define PIPE 8
# define ENV 9
# define VAR 11

# define PROMPT		0
# define EOT		100

typedef struct s_node
{
	char			*name;
	char			*value;
	struct s_node	*next;
}	t_node;

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_token
{
	char			*str;
	int				type;
	int				quote;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_mini
{
	t_token		*tokens;
	int			cmd;
	int			pipe_read;
	int			pipe_write;
	int			input;
	int			output;
	int			stdin;
	int			stdout;
	int			execute_code;
	int			heredoc;
	int			heredoc_next_delim;
	int			heredoc_process_delim;
	char		*heredoc_buff;
	t_token		*heredoc_next_token;
	t_list		*env;
	t_node		*env_list;
	t_var		*var_list;
}	t_mini;

int		g_exit_num;

//main
void	init_main(int argc, char **argv);
t_mini	*init_mini(void);

//parse

void	parse(t_mini *mini, char *input);
char	**ft_new_split(char *s);
char	*ft_strtok(char *str, const char *delimiters);
int		ft_strcmp(char *s1, char *s2);
char	*add_spaces_around_pipe(const char *s);
char	*checkinsidestruct(t_node *env_list2, t_var *env_list, char *name);

//token
t_token	*new_token(t_mini *mini, char *data);
void	token_addend(char *data, t_mini *mini);
int		builtin_cmd(char *token);
int		delim_token(char *token);

//quote
int		closed_quote(char *line);
int		closed_dub_quote(char *line);
int		ft_dollar(char *new);
char	*ft_delete_quote(char *data);
char	*ft_delete_quote_sin(char *data);
int		detect_q(char *data);
int		ft_double_detect_quote(char *data);
char	*dollar_exit(char *av);

//execute
int		execute(t_mini *mini);
char	*ft_strremove(char *str, const char *sub);
int		count_argc(char **args);
char	**convert_argv(t_token	*tokens);
int		execute_builtin(char **argv, char *command, t_mini *ms);

//builtin
int		find_substring(const char *string, const char *substring);
int		ft_export(char **str, t_mini *ms);
int		echo(int argc, char **argv, t_token curr,
			t_mini *mini);
int		cd(int argc, char **argv, t_node **env_list);
int		pwd(void);
int		mini_exit(char **argv);
void	ft_prev_dir(char *path);
void	ft_home_dir(void);

//execve
int		call_cmd(char **av, t_mini *ms);
int		it_works(char *cmd_path);

//pipe
void	call_pipe_redirect(t_mini *mini, t_token *command, t_token *tok);
int		redirect_output(t_mini *ms, t_token *token, int type);
int		redirect_input(t_mini *ms, t_token *token);
void	here_doc_input(t_mini *mini, t_token *command, int pid);
void	handle_pipe_character(const char *s, size_t i,
			char **result, size_t *j);

//heredoc
int		create_temporary_file(void);
void	get_and_write_input(int tmp_fd, char *eof);
void	clear_tmp_file_input(void);
void	make_tmp_file_trunc(char *str);
void	make_tmp_file_input(void);

//signal
void	define_signal(void);
void	int_handler(int signal);

//var
t_var	*var_initialize_var(void);
t_var	*var_create_node(char *name, char *value);
void	free_var(t_var *head);
void	var_insert_node(t_var **head, char *name, char *value);
char	*var_get_env_value(t_var *env_list, char *name);
void	var_print_list(t_var *head);
void	remove_dollar_sign(char **str);

//env
t_node	*get_terminal_env_list(char *env[]);
char	*get_env_value(t_node *env_list, char *name);
void	free_head(t_node *head);
char	**ft_getenv(t_node *envList);
void	print_list(t_node *head);
void	delete_node(t_node **head, char **name);
void	insert_node(t_node **head, char *name, char *value);
int		get_env_count(t_node *envList);
void	allocate_env_variable(char **variable, t_node *current, int i);

//free
void	agrv_free(char **argv);
void	token_free(t_token *tok);

#endif
