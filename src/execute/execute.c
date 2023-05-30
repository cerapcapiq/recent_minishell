/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:04:49 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 15:43:56 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute(t_mini *mini)
{
	char	**argv;
	t_token	*tok;
	t_token	*command;
	int		i;
// char	exit_status[16];

	tok = mini->tokens;
	while (tok)
	{
		command = tok;
		argv = convert_argv(command);
		tok = tok->next;
		while (tok && tok->type == ARG)
			tok = tok->next;
		i = 0;
		// while (argv[i] != NULL)
		// {
		// 		printf("inside howute\n\n");
		// 	if (find_substring(argv[i], "$?") == 0)
		// 	{				
		// 		snprintf(exit_status, sizeof(exit_status), "%d", g_exit_num);
		// 		argv[i] = exit_status;
		// 	}
		// 	i++;
		// }
		call_pipe_redirect(mini, command, tok);
		if (command->type == BUILTIN || command->type == VAR)
			mini->execute_code = execute_builtin(argv, command->str, mini);
		else if (command->type == CMD)
			mini->execute_code = call_cmd(argv, mini);
	}
	wait(NULL);
	return (0);
}
