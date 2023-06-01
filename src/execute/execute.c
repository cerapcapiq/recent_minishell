/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:04:49 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/01 16:46:00 by gualee           ###   ########.fr       */
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

void	execute_command(t_mini *mini, t_token *command)
{
	char	**argv;
	int		i;

	argv = convert_argv(command);
	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i] != NULL)
	{
		if (find_substring(argv[i], "$") != -1)
			argv[i] = check_dollar(mini, argv[i]);
		i++;
	}
	call_pipe_redirect(mini, command, command->next);
	mini->execute_code = execute_other(argv, mini);
}

int	execute(t_mini *mini)
{
	t_token	*tok;

	tok = mini->tokens;
	while (tok)
	{
		execute_command(mini, tok);
		tok = tok->next;
		while (tok && tok->type == ARG)
			tok = tok->next;
	}
	wait(NULL);
	return (0);
}
