/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:15:45 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/26 16:32:28 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	create_pipe(t_mini *mini)
{
	int		fd[2];
	int		status;

	status = pipe(fd);
	if (status < 0)
	{
		mini->pipe_read = -1;
		mini->pipe_write = -1;
		return (0);
	}
	mini->pipe_read = fd[0];
	mini->pipe_write = fd[1];
	return (1);
}

void	call_pipe_redirect(t_mini *mini, t_token *command, t_token *tok)
{
	if (!command)
		return ;
	if (tok && tok->type == PIPE)
	{
		create_pipe(mini);
		tok = tok->next;
	}
	else if (tok && (tok->type == TRUNC || tok ->type == APPEND))
	{
		tok = tok->next;
		tok->type = ARG;
		redirect_output(mini, tok, tok->prev->type);
	}
	else if (tok && (tok->type == INPUT))
	{
		tok = tok->next;
		tok->type = ARG;
		redirect_input(mini, tok);
	}
	else if (tok && tok->type == HEREDOC)
	{	
		tok = tok->next;
		tok->type = ARG;
		here_doc_input(tok, 0);
	}
}
