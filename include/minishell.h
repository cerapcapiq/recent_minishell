
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
#include <sys/stat.h>

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

int g_exit_num;

typedef struct Node {
    char* name;
    char* value;
    struct Node* next;
} Node;

typedef struct MyNode {
    char* name;
    char* value;
    struct MyNode* next;
} MyNode;

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
	t_list		*env;
	Node* envListHead;
	MyNode*   varListHead;
}	t_mini;


//parse

void	parse(t_mini *mini, char *input);
char	**ft_new_split(char *s, char c);
char* ft_strtok(char* str, const char* delimiters);
int	ft_strcmp(char *s1, char *s2);
char* add_spaces_around_pipe(const char* s);

//token
t_token	*new_token(t_mini *mini, char *data);
void	token_addend(char *data, t_mini *mini);

//quote
int	closed_quote(char *line);
int	closed_dub_quote(char *line);
int	ft_dollar(char *new);
char *ft_delete_quote(char* data);
char *ft_delete_quote_sin(char* data);
int	detect_q(char *data);
int	ft_double_detect_quote(char *data);

//execute
int	execute(t_mini *mini);
char	*ft_strremove(char *str, const char *sub);
int	count_argc(char **args);
char	**convert_argv(t_token	*tokens);
int	execute_builtin(char **argv, char *command, t_mini *ms);

//builtin
int findSubstring(const char* string, const char* substring);
void	ft_export(char **str, Node* envListHead, MyNode *varListHead);
int	echo(int argc, char **argv, t_token curr, MyNode *varListHead, Node* envListHead);
int     cd(int argc, char **argv, Node* envListHead);
int	pwd(void);
int	mini_exit(char **argv);
void	ft_prev_dir(char *path);
void	ft_home_dir(void);

//execve
int	call_cmd(char **av, t_mini *ms);
int	it_works(char *cmd_path);

//pipe
void	call_pipe_redirect(t_mini *mini, t_token *command, t_token *tok);
int	redirect_output(t_mini *ms, t_token *token, int type);
int	redirect_input(t_mini *ms, t_token *token);
void	here_doc_input(t_token *command, int pid);

//signal
void	define_signal(void);


//var
MyNode* var_initializeMyNode();
void free_Var(MyNode* head);
void var_insertNode(MyNode** head, char* name, char* value);
char* var_getEnvValue(MyNode *envListHead, char* name);
void var_printList(MyNode* head);


//env
Node* getTerminalEnvList(char* env[]);
char* getEnvValue(Node *envListHead, char* name);
void free_Head(Node* head);
char **ft_getenv(Node *envList);
void printList(Node* head);
void deleteNode(Node** head, char** name);
void insertNode(Node** head, char* name, char* value);

//free
void	agrv_free(char **argv);
void	token_free(t_token *tok);

#endif