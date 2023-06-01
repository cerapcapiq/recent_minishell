/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:06:28 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/01 13:07:48 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

int	call_builtin(char **argv, char *command, t_token token, t_mini *ms)
{
	int	argc;
	int	builtin_cmd;

	builtin_cmd = 0;
	argc = count_argc(argv);
	if (!ft_strcmp(command, "echo"))
	{
		if (argc < 2 || (!ft_strcmp(argv[1], "-n")))
			printf("\n");
		else
			builtin_cmd = echo(argc, argv, *token.next, ms);
	}
	else if (!ft_strcmp(command, "pwd"))
		builtin_cmd = pwd();
	else if (!ft_strcmp(command, "export"))
		builtin_cmd = ft_export(argv, ms->env_list, ms->var_list);
	else if (!ft_strcmp(command, "env"))
		print_list(ms->env_list);
	else if (!ft_strcmp(command, "unset"))
		delete_node(&ms->env_list, argv);
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
		exit_code = cd(argc, argv, &ms->env_list);
	else if (!ft_strcmp(command, "exit"))
		mini_exit(argv);
	else if (!ft_strcmp(command, "export"))
		exit_code = ft_export(argv, ms->env_list, ms->var_list);
	else if (!ft_strcmp(command, "unset"))
		delete_node(&ms->env_list, argv);
	g_exit_num = exit_code;
	ms->execute_code = exit_code;
}

static void	create_fork(pid_t *pid, int *status_code)
{
	*pid = fork();
	*status_code = 0;
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
		post_call(argv, command, ms, exit_code);
	}
	return (WEXITSTATUS(exit_code));
}
