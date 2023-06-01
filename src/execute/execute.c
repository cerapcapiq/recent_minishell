/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:04:49 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/01 16:11:33 by abasarud         ###   ########.fr       */
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

int	execute_other(char **argv, t_mini *mini)
{
	int	exit;

	exit = mini->execute_code;
	if (mini->tokens->type == BUILTIN)
		mini->execute_code = execute_builtin(argv, mini->tokens->str, mini);
	else if (mini->tokens->type == CMD)
		mini->execute_code = call_cmd(argv, mini);
	return (mini->execute_code);
}

int	execute(t_mini *mini)
{
	char	**argv;
	t_token	*tok;
	t_token	*command;
	int		i;

	tok = mini->tokens;
	while (tok)
	{
		command = tok;
		argv = convert_argv(command);
		i = 0;
		while (argv[i] != NULL)
		{
			if (find_substring(argv[i], "$") != -1)
				argv[i] = check_dollar(mini, argv[i]);
			i++;
		}
		tok = tok->next;
		while (tok && tok->type == ARG)
			tok = tok->next;
		call_pipe_redirect(mini, command, tok);
		mini->execute_code = execute_other(argv, mini);
	}
	wait(NULL);
	return (0);
}
