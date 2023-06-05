/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:42 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/04 20:58:30 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

int	if_var(char *token)
{
	char	c;

	c = '=';
	while (*token != '\0')
	{
		if (*token == c)
		{
			printf("the toke n var");
			return (VAR);
			break ;
		}
		token++;
	}
	return (0);
}

int	token_type(t_mini *mini, char *token)
{
	char	*name;
	char	*value;

	if (delim_token(token))
	{
		mini->cmd = 1;
		return (delim_token(token));
	}
	if (!mini->cmd)
		return (ARG);
	else
		mini->cmd = 0;
	if (builtin_cmd(token))
		return (BUILTIN);
	else if (if_var(token))
	{
		name = strtok(token, "=");
		value = strtok(NULL, "=");
		var_insert_node(&mini->var_list, name, value);
		return (VAR);
	}
	else
		return (CMD);
	return (0);
}

int	token_quote_type(char *data)
{
	int	quote;

	if (detect_q(data))
		quote = 1;
	else if (ft_double_detect_quote(data))
		quote = 2;
	else
		quote = 0;
	return (quote);
}

t_token	*new_token(t_mini *mini, char *data)
{
	t_token	*res;
	char	*new;
	int		quote_type;

	quote_type = 0;
	res = (t_token *)malloc(sizeof(t_token));
	res->quote = token_quote_type(data);
	if (res->quote == 2)
		res->str = ft_delete_quote(data);
	else if (res->quote == 1)
		res->str = ft_delete_quote_sin(data);
	if (res->quote != 0)
		res->type = ARG;
	new = ft_strdup(data);
	res->type = token_type(mini, data);
	res->str = ft_strdup(new);
	res->prev = 0;
	res->next = 0;
	return (res);
}

void	token_addend(char *data, t_mini *mini)
{
	t_token	*tok;
	t_token	*temp;

	printf("token is : %s\n", data);
	tok = mini->tokens;
	while (tok->next)
		tok = tok->next;
	temp = new_token(mini, data);
	tok->next = temp;
	tok->next->prev = tok;
}
