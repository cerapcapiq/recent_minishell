/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:40 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 18:23:04 by abasarud         ###   ########.fr       */
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

void	parse(t_mini *mini, char *input)
{
	char	**split;
	int		i;
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
	first = new_token(mini, *split);
	mini->tokens = first;
	i = 0;
	while (split[++i])
		token_addend(split[i], mini);
	execute(mini);
	mini->cmd = 1;
	token_free(mini->tokens);
	agrv_free(split);
}
