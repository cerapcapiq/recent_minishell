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

char	*ft_newstrstr(const char* haystack, const char* needle)
{
    if (*needle == '\0') {
        return (char*)haystack;
    }

    while (*haystack) {
        const char* h = haystack;
        const char* n = needle;

        while (*h && *n && (*h == *n)) {
            h++;
            n++;
        }

        if (*n == '\0') {
            return (char*)haystack;
        }

        haystack++;
    }

    return NULL;
}

char	*ft_strtok(char *str, const char *delimiter)
{
    static char *token = NULL;
    if (str != NULL)
        token = str;
    if (token == NULL)
        return NULL;
    char* delimiter_ptr = ft_newstrstr(token, delimiter);
    if (delimiter_ptr == NULL)
	{
        char* temp = token;
        token = NULL;
        return temp;
    }
    *delimiter_ptr = '\0';
    char* current_token = token;
    token = delimiter_ptr + ft_strlen(delimiter);
    return (current_token);
}

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

int already_exist(t_node *env_list, char *cpy)
{
	t_node	*current;

	current = env_list;
	while (current != NULL)
	{
		if (!ft_strcmp(current->name, cpy))
				return (1);
		current = current->next;
	}
	return (0);
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
		cpy = ft_strtok(str[i], "=");
		new = ft_strtok(NULL, "=");
	}
	else
	{
		cpy = ft_strdup(str[i]);
		new = var_get_env_value(mini->var_list, cpy);
		if (new == NULL)
			return (0);
	}
	if (already_exist(mini->env_list, cpy) == 0)
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
