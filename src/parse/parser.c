/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:40 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/06 15:47:49 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

char	*dollar_exit(char *av)
{
	char	*exit_status;

	exit_status = NULL;
	if (!ft_strcmp(av, "$?"))
		exit_status = ft_itoa(g_exit_num);
	return (exit_status);
}

void	create_tokens(t_mini *mini, char **split)
{
	t_token	*first;
	int		i;

	first = NULL;
	i = 0;
	first = new_token(mini, *split);
	mini->tokens = first;
	while (split[++i])
		token_addend(split[i], mini);
}

void	free_parser(char **split, t_mini *mini)
{
	token_free(mini->tokens);
	agrv_free(split);
}

void	parse(t_mini *mini, char *input)
{
	char	**split;
	int		k;
	t_token	*first;
	char	*cpy;

	cpy = NULL;
	first = NULL;
	split = NULL;
	if (input == NULL)
		exit(0);
	input = add_spaces_around_pipe(input);
	cpy = ft_strdup(input);
	split = ft_new_split(cpy, ' ');
	k = 0;
	while (split[k])
	{
		if (!ft_strcmp(split[k], "$?"))
			split[k] = dollar_exit(split[k]);
		k++;
	}
	create_tokens(mini, split);
	execute(mini);
	mini->cmd = 1;
	free_parser(split, mini);
}
