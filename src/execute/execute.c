/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:04:49 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/17 17:35:43 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_dollar(t_mini *mini, char *name)
{
	char	*value;

	if (mini->tokens->type != CMD)
		return (name);
	if (closed_dub_quote(name))
			name = ft_delete_quote(name);
	else if (closed_quote(name))
		name = ft_delete_quote_sin(name);
	if (*name == '$')
		name++;
	value = var_get_env_value(mini->var_list, name);
	if (value != NULL)
		return (value);
	value = get_env_value(mini->env_list, name);
	if (value != NULL)
		return (value);
	name = ft_strjoin("$", name);
	return (name);
}

void	replace_dollar_variables(t_mini *mini, char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		if (find_substring(argv[i], "$") != -1)
			argv[i] = check_dollar(mini, argv[i]);
		i++;
	}
}

int execute_others(t_mini *mini, t_token *command, char **argv)
{
    int exit_code = 0;
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        // Child process
        if (command->type == BUILTIN || command->type == VAR)
            mini->execute_code = execute_builtin(argv, command->str, mini);
        else if (command->type == CMD)
        {
            replace_dollar_variables(mini, argv);
            mini->execute_code = call_cmd(argv, mini);
        }
        exit_code = mini->execute_code;
        exit(exit_code);
    }
    else if (pid > 0)
    {
        // Parent process
        // Wait for the child process to finish
        while (waitpid(pid, &exit_code, 0) == -1)
            continue;

        return WEXITSTATUS(exit_code);
    }
    else
    {
        // Fork failed
        return -1;
    }
}

int	execute(t_mini *mini)
{
	t_token	*tok;
	t_token	*command;
	char	**argv;

	tok = mini->tokens;
	while (tok)
	{
		command = tok;
		argv = convert_argv(command);
		tok = tok->next;
		while (tok && tok->type == ARG)
			tok = tok->next;
		call_pipe_redirect(mini, command, tok);
		mini->execute_code = execute_others(mini, command, argv);
	}
	wait(NULL);
	return (0);
}
