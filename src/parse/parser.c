/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:40 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 15:45:58 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

char	*dollar_exit(char *av)
{
	char	exit_status[16];

	if (!ft_strcmp(av, "$?"))
	{
		snprintf(exit_status, sizeof(exit_status), "%d", g_exit_num);
		strcpy(av, exit_status);
	}
	return (av);
}

void	parse(t_mini *mini, char *input)
{
	char	**split;
	int		i;
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
	first = new_token(mini, *split);
	mini->tokens = first;
	i = 0;
	while (split[++i])
		token_addend(split[i], mini);
	dollar_exit(*split);
	execute(mini);
	mini->cmd = 1;
	token_free(mini->tokens);
	agrv_free(split);
}
