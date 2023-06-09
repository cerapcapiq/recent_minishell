/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:58:39 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/07 17:10:46 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>

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

int	ft_export(char **str, t_mini *mini)
{
	int		i;
	char	*new;
	int		flag;
	char	*cpy;

	flag = 0;
	i = 1;
	new = NULL;
	if (*str[1] == '$')
		ft_memmove(str[i], str[i] + 1, ft_strlen(str[i]));
	while (str[i] != NULL)
	{
		if (find_substring(str[i], "=") != -1)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	i = 1;
	if (flag == 1)
	{
		cpy = strtok(str[i], "=");
		new = strtok(NULL, "=");
	}
	else
	{
		cpy = ft_strdup(str[i]);
		new = var_get_env_value(mini->var_list, cpy);
		if (new == NULL)
			return (0);
	}
	insert_node(&mini->env_list, cpy, new);
	return (0);
}

void	ft_unset(char **str)
{
	int	i;

	i = 1;
	printf("all the %s", str[i]);
	return ;
}
