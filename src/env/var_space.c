/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:22:01 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 15:35:57 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char	**var_ft_getenv(t_var *envList)
{
	int		count;
	int		i;
	int		len;
	t_var	*current;
	char	**variable;

	count = 0;
	current = envList;
	variable = NULL;
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
		len = ft_strlen(current->name) + strlen(current->value) + 2;
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

void	var_delete_node(t_var **head, char **name)
{
	int		i;
	t_var	*current;
	t_var	*previous;

	i = 1;
	if (*head == NULL)
		printf("nono\n");
	if (name[i] == NULL)
		printf("nothing\n");
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

void	free_var(t_var	*head)
{
	t_var	*current;
	t_var	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}

void	var_print_list(t_var *head)
{
	t_var	*current;

	current = head;
	if (current == NULL)
		printf("booba\n");
	while (current != NULL)
	{
		printf("%s=%s->\n", current->name, current->value);
		current = current->next;
	}
	if (current == NULL)
		printf("booba\n");
	return ;
}

t_var	*var_initialize_var(void)
{
	t_var	*var_list;

	var_list = NULL;
	var_insert_node(&var_list, "starting", "minishell");
	return (var_list);
}
