
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

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*buffer;
	char		*token;
	char		*delimiter;

	buffer = NULL;
	if (str != NULL)
		buffer = str;
	if (buffer == NULL || *buffer == '\0')
		return (NULL);

	token = buffer;
	delimiter = ft_strpbrk(buffer, delimiters);

	if (delimiter != NULL)
	{
		*delimiter = '\0';
		buffer = delimiter + 1;
	}
	else
		buffer += ft_strlen(buffer);
	return (token);
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
