/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:55:34 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/07 17:08:56 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

int	for_env(char *token)
{
	if (find_substring(token, "="))
	{
		return (ENV);
		printf("in able env\n");
	}
	return (0);
}

char	*get_env_value(t_node *env_list, char *name)
{
	t_node	*current;

	current = env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	delete_node(t_node **head, char **name)
{
	int		i;
	t_node	*current;
	t_node	*previous;

	i = 1;
	if (*head == NULL || name[i] == NULL)
		printf("nono\n");
	if (*name[1] == '$')
		ft_memmove(name[1], name[1] + 1, ft_strlen(name[1]));
	name[i] = strtok(name[i], "=");
	current = *head;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name[i]) == 0)
		{
			if (previous == NULL)
				*head = current->next;
			else
				previous->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
	previous = current;
	current = current->next;
	}
}

void	print_list(t_node *head)
{
	t_node	*current;

	current = head;
	if (current == NULL)
	{
		printf("NULL\n");
		return ;
	}
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	if (current == NULL)
		printf("NULL\n");
	return ;
}
