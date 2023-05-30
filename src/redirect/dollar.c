/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:41:16 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 18:22:04 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	ft_detect_dollar(char	*s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_dollar(char *new)
{
	while (*new != '\0')
	{
		if (*new == '$')
			return (1);
		new++;
	}
	return (0);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_delete_quote(char *data)
{
	int		len;
	char	*new;

	len = ft_strlen(data);
	new = NULL;
	if (len >= 2 && data[0] == '"' && data[len - 1] == '"')
	{
		ft_memmove(data, data + 1, len - 2);
		data[len - 2] = '\0';
	}
	new = data;
	return (new);
}

char	*ft_delete_quote_sin(char *data)
{
	int		len;
	char	*new;

	len = ft_strlen(data);
	new = NULL;
	if (len >= 2 && data[0] == '\'' && data[len - 1] == '\'')
	{
		ft_memmove(data, data + 1, len - 2);
		data[len - 2] = '\0';
	}
	new = data;
	return (new);
}
