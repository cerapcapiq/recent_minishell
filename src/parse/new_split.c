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

#include <stdlib.h>
#include <string.h>

static void copyString(char *destination, char *begin, char *end)
{
    while (begin < end)
        *(destination++) = *(begin++);
    *destination = '\0';
}

static int handleQuotes(char **str)
{
    char quote = **str;
    if (!(quote == '\"' || quote == '\''))
        return 0;
    (*str)++;
    while (**str && **str != quote)
        (*str)++;
    if (**str == quote)
        (*str)++;
    return 1;
}

static int countWords(char *str, char delimiter)
{
    int count = 0;
    while (*str)
    {
        if (!(*str == delimiter))
        {
            count++;
            if (handleQuotes(&str))
                continue;
            while (*str && !(*str == delimiter))
                str++;
        }
        else
            str++;
    }
    return count;
}

static int extractQuotes(char **result, char *start, int *index, char **str)
{
    char quote = **str;
    if (!(quote == '\"' || quote == '\''))
        return 0;
    (*str)++;
    while (**str && **str != quote)
        (*str)++;
    if (**str == quote)
        (*str)++;
    result[*index] = (char *)malloc((char *)*str - start + 1);
    copyString(result[(*index)++], start, (char *)*str);
    return 1;
}

char **ft_new_split(char *str)
{
    char *start;
    char **result;
    char delimiter = ' ';
    int index = 0;

    if (!str)
        return NULL;

    result = (char **)malloc((sizeof(char *) * (countWords((char *)str, delimiter) + 1)));

    while (*str)
    {
        if (*str != delimiter)
        {
            start = (char *)str;
            if (extractQuotes(result, start, &index, &str))
                continue;
            while (*str && *str != delimiter)
                str++;
            result[index] = (char *)malloc((char *)str - start + 1);
            copyString(result[index++], start, (char *)str);
        }
        else
            str++;
    }
    result[index] = NULL;
    return result;
}

