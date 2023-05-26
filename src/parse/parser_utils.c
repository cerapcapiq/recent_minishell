
#include "../include/minishell.h"

char* ft_strpbrk(const char* string, const char* charset) {
    while (*string != '\0') {
        const char* ptr = charset;
        while (*ptr != '\0') {
            if (*string == *ptr) {
                return (char*)string;
            }
            ptr++;
        }
        string++;
    }
    return NULL;
}

char* ft_strtok(char* str, const char* delimiters)
{
    static char* buffer = NULL;
    if (str != NULL) {
        buffer = str;
    }

    if (buffer == NULL || *buffer == '\0') {
        return NULL;
    }

    char* token = buffer;
    char* delimiter = ft_strpbrk(buffer, delimiters);

    if (delimiter != NULL) {
        *delimiter = '\0';
        buffer = delimiter + 1;
    } else {
        buffer += ft_strlen(buffer);
    }

    return token;
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

char* add_spaces_around_pipe(const char* s)
{
    size_t len = ft_strlen(s);
    char* result = malloc(sizeof(char) * (len * 2 + 1));
    if (!result) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (s[i] == '|' && ((i > 0 || s[i-1] != ' ') || (i < len - 1 || s[i+1] != ' '))) {
            result[j++] = ' ';
            result[j++] = '|';
            result[j++] = ' ';
        } else {
            result[j++] = s[i];
        }
    }
    result[j] = '\0';

    return result;
}