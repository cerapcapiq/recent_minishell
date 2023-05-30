/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_space_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:00:17 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 18:28:03 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	var_delete_node(t_var **head, char **name)
{
	int		i;
	t_var	*current;
	t_var	*previous;

	i = 1;
	if (*head == NULL || name[i] == NULL)
		printf("nono\n");
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
