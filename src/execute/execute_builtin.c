
#include "../include/minishell.h"
//calls the builtin function for execution

int	call_builtin(char **argv, char *command, t_token token, t_mini *ms)
{
	int	argc;
	int	builtin_cmd = 0;

	if (token.type != VAR)
		argc = count_argc(argv);
	builtin_cmd = 0;
	if (!ft_strcmp(command, "echo"))
		builtin_cmd = echo(argc, argv, *token.next, ms->varListHead,ms->envListHead);
	else if (!ft_strcmp(command, "pwd"))
		builtin_cmd = pwd();
	else if (!ft_strcmp(command, "export"))
	 	 //insertNode(&envListHead, command, *argv);
		  ft_export(argv, ms->envListHead, ms->varListHead);
	else if (!ft_strcmp(command, "env"))
		printList(ms->envListHead);
	else if (!ft_strcmp(command, "unset"))
		 deleteNode(&ms->envListHead, argv);

	g_exit_num = builtin_cmd;
	return (builtin_cmd);
}

static	void	post_call(char **argv, char *command, t_mini *ms, int exit_code)
{
	int	argc;
	
if (ms->tokens->type != VAR)
		argc = count_argc(argv);
	exit_code = 0;
	if (!ft_strcmp(command, "cd"))
		cd(argc, argv, ms->envListHead);
	else if (!ft_strcmp(command, "exit"))
		mini_exit(argv);
else if (!ft_strcmp(command, "export"))
	 	 //insertNode(&envListHead, command, *argv);
		  ft_export(argv, ms->envListHead, ms->varListHead);
	else if (!ft_strcmp(command, "unset"))
		 deleteNode(&ms->envListHead, argv);
	ms->execute_code = exit_code;
}

static void	create_fork(pid_t *pid, int *status_code)
{
	*pid = fork();
	*status_code = 0;
	//g_global.in_fork = 1;
}

static void	call_nice(t_mini *mini, char *cmd, char **args)
{
	int	status_code;

	status_code = call_builtin(args, cmd, *mini->tokens, mini);
	exit(status_code);
}


int	execute_builtin(char **argv, char *command, t_mini *ms)
{
	pid_t	pid;
	int		exit_code;
	
	create_fork(&pid, &exit_code);
	if (pid == 0)
	{
		if (ms->pipe_write != -1)
		{
			close(ms->pipe_read);
			dup2(ms->pipe_write, STDOUT_FILENO);
		}
		call_nice(ms, command, argv);
	}
	else
	{	
		if (ms->pipe_read != -1)
		{
			
			dup2(ms->pipe_read, STDIN_FILENO);
			close(ms->pipe_write);
		}
		waitpid(pid, &exit_code, 0);
		post_call(argv, command,  ms, exit_code);
	}
	return (WEXITSTATUS(exit_code));
}