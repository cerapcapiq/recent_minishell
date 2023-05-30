/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:21:54 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 12:21:54 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char	**ft_getenv(t_node *envList)
{
	int		count;
	t_node	*current;
	char	**variable;
	int		i;
	int		len;

	current = envList;
	variable = NULL;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	variable = (char **)malloc((count + 1) * sizeof(char *));
	if (variable == NULL)
		return (NULL);
	current = envList;
	i = 0;
	while (current != NULL)
	{
		len = ft_strlen(current->name) + ft_strlen(current->value) + 2;
		variable[i] = (char *)malloc(len * sizeof(char));
		snprintf(variable[i], len, "%s=%s", current->name, current->value);
		if (it_works(variable[i]))
			break ;
		current = current->next;
		i++;
	}
	variable[i] = NULL;
	return (variable);
}

char	*get_path_value(t_node *env_list, int index)
{
	char	*path;
	char	*token;

	path = NULL;
	token = strtok(path, ":");
	path = get_env_value(env_list, "PATH");
	if (path == NULL)
		return (NULL);
	token = strtok(path, ":");
	while (token != NULL && index > 0)
	{
		token = strtok(NULL, ":");
		index--;
	}
	return (token);
}

t_node	*create_node(char *name, char *value)
{
	t_node	*newt_node;

	newt_node = (t_node *)malloc(sizeof(t_node));
	newt_node->name = ft_strdup(name);
	newt_node->value = ft_strdup(value);
	newt_node->next = NULL;
	return (newt_node);
}

void	insert_node(t_node **head, char *name, char *value)
{
	t_node	*newt_node;
	t_node	*current;

	newt_node = create_node(name, value);
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

t_node	*get_terminal_env_list(char *env[])
{
	t_node	*env_list;
	char	*variable;
	char	*name;
	char	*value;
	int		i;

	env_list = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		variable = env[i];
		name = strtok(variable, "=");
		value = strtok(NULL, "=");
		insert_node(&env_list, name, value);
		i++;
	}
	return (env_list);
}
