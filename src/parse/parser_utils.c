/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:37 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/07 16:55:47 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strpbrk(const char *string, const char *charset)
{
	const char	*ptr;

	while (*string != '\0')
	{
		ptr = charset;
		while (*ptr != '\0')
		{
			if (*string == *ptr)
				return ((char *)string);
			ptr++;
		}
		string++;
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
