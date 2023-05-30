/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:58:39 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 14:17:17 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_substring(const char *string, const char *substring)
{
	int	stringlen;
	int	substringlen;
	int	j;
	int	i;

	stringlen = ft_strlen(string);
	substringlen = ft_strlen(substring);
	i = 0;
	while (i <= stringlen - substringlen)
	{
		j = 0;
		while (j < substringlen)
		{
			if (string[i + j] != substring[j])
				break ;
			j++;
		}
		if (j == substringlen)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_export(char **str, t_node *env_list, t_var *var_list)
{
	int		i;
	char	*new;

	i = 1;
	new = NULL;
	new = var_get_env_value(var_list, str[i]);
	insert_node(&env_list, str[i], new);
}

void	ft_unset(char **str)
{
	int	i;

	i = 1;
	printf("all the %s", str[i]);
	return ;
}
