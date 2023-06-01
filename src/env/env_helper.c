/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:35:35 by gualee            #+#    #+#             */
/*   Updated: 2023/06/01 11:21:36 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_env_count(t_node *envList)
{
	int		count;
	t_node	*current;

	count = 0;
	current = envList;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	allocate_env_variable(char **variable, t_node *current, int i)
{
	int	len;

	len = ft_strlen(current->name) + ft_strlen(current->value) + 2;
	variable[i] = (char *)malloc(len * sizeof(char));
	if (variable[i] != NULL)
		snprintf(variable[i], len, "%s=%s", current->name, current->value);
}
