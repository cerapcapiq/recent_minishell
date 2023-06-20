/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:33 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 13:24:16 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_strcpy(char *dst, char *begin, char *end)
{
	while (begin < end)
		*(dst++) = *(begin++);
	*dst = 0;
}

static int	handle_quotes_tw(char **s)
{
	char	quote;

	quote = **s;
	if (!(quote == '\"' || quote == '\''))
		return (0);
	(*s)++;
	while (**s && **s != quote)
		(*s)++;
	if (**s == quote)
		(*s)++;
	return (1);
}

static int	get_tw(char *s, char c)
{
	int		res;

	res = 0;
	while (*s)
	{
		if (!(*s == c))
		{
			res++;
			if (handle_quotes_tw(&s))
				continue ;
			while (*s && !(*s == c))
				s++;
		}
		else
			s++;
	}
	return (res);
}

static int	quotes(char **res, char *start, int *i, char **s)
{
	char	quote;

	quote = **s;
	if (!(quote == '\"' || quote == '\''))
		return (0);
	(*s)++;
	while (**s && **s != quote)
		(*s)++;
	if (**s == quote)
		(*s)++;
	res[*i] = (char *)malloc((char *)*s - start + 1);
	ft_strcpy(res[(*i)++], start, (char *)*s);
	return (1);
}

char	**ft_new_split(char *s)
{
	char	*start;
	char	**res;
	char	c;
	int		i;

	if (!s)
		return (0);
	c = ' ';
	res = (char **)malloc((sizeof(char *) * (get_tw((char *)s, c) + 1)));
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = (char *)s;
			if (quotes(res, start, &i, &s))
				continue ;
			while (*s && *s != c)
				s++;
			res[i] = (char *)malloc((char *)s - start + 1);
			ft_strcpy(res[i++], start, (char *)s);
		}
		else
			s++;
	}
	res[i] = 0;
	return (res);
}
