/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:04:49 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 18:27:25 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute(t_mini *mini)
{
	char	**argv;
	t_token	*tok;
	t_token	*command;

	tok = mini->tokens;
	while (tok)
	{
		command = tok;
		argv = convert_argv(command);
		tok = tok->next;
		while (tok && tok->type == ARG)
			tok = tok->next;
		call_pipe_redirect(mini, command, tok);
		if (command->type == BUILTIN)
			mini->execute_code = execute_builtin(argv, command->str, mini);
		else if (command->type == CMD)
			mini->execute_code = call_cmd(argv, mini);
	}
	wait(NULL);
	return (0);
}

		// i = 0;
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