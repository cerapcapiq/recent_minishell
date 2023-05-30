/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:22:01 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 18:01:34 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char	*var_get_env_value(t_var *env_list, char *name)
{
	t_var	*current;

	current = env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

t_var	*var_create_node(char *name, char *value)
{
	t_var	*newt_node;

	newt_node = (t_var *)malloc(sizeof(t_var));
	newt_node->name = strdup(name);
	newt_node->value = strdup(value);
	newt_node->next = NULL;
	return (newt_node);
}

void	var_insert_node(t_var **head, char *name, char *value)
{
	t_var	*newt_node;
	t_var	*current;

	newt_node = var_create_node(name, value);
	if (*head == NULL)
		*head = newt_node;
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = newt_node;
	}
}

t_var	*var_initialize_var(void)
{
	t_var	*var_list;

	var_list = NULL;
	var_insert_node(&var_list, "starting", "minishell");
	return (var_list);
}
