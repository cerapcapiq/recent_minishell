/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_space_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:21:27 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/01 12:24:20 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_variables(t_var *env_list)
{
	int		count;
	t_var	*current;

	count = 0;
	current = env_list;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**allocate_memory(int count)
{
	return ((char **)malloc(count * sizeof(char *)));
}

char	*create_variable_string(const char *name, const char *value, int len)
{
	char	*variable;

	variable = (char *)malloc(len * sizeof(char));
	snprintf(variable, len, "%s=%s", name, value);
	return (variable);
}

void	copy_variables(t_var *env_list, char **variable)
{
	int		i;
	int		len;
	t_var	*current;

	i = 0;
	current = env_list;
	while (current != NULL)
	{
		len = ft_strlen(current->name) + ft_strlen(current->value) + 2;
		variable[i] = create_variable_string(current->name,
				current->value, len);
		if (it_works(variable[i]))
			break ;
		current = current->next;
		i++;
	}
	variable[i] = NULL;
}

char	**var_ft_getenv(t_var *envList)
{
	int		count;
	char	**variable;

	count = count_variables(envList);
	variable = allocate_memory(count + 1);
	if (variable == NULL)
		return (NULL);
	copy_variables(envList, variable);
	return (variable);
}
