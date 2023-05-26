


#include "../include/minishell.h"

char* ft_strstr(const char* haystack, const char* needle) {
    if (*needle == '\0') {
        return (char*)haystack;
    }

    while (*haystack) {
        const char* h = haystack;
        const char* n = needle;

        while (*haystack && *n && *haystack == *n) {
            haystack++;
            n++;
        }

        if (*n == '\0') {
            return (char*)h;
        }

        haystack = h + 1;
    }

    return NULL;
}

char	*ft_strremove(char *str, const char *sub)
{
	char	*p;
	char	*q;
	char	*r;
	size_t	len;

	if (*sub)
	{
		q = ft_strstr(str, sub);
		r = q;
		if (q != NULL)
		{
			len = ft_strlen(sub);
			while (r != NULL)
			{
				p = r + len;
				r = ft_strstr(p, sub);
				while (p < r)
					*q++ = *p++;
			}
			while (*q != '\0')
				*q++ = *p++;
		}
	}
	return (str);
}

int	count_argc(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}

char	**convert_argv(t_token	*tokens)
{
	int		i;
	t_token	*tok;
	char	**res;

	i = 0;
	tok = tokens;
	while (tok && (tok->type == ARG || tok->type == BUILTIN
			|| tok->type == CMD || tok->type == 9))
	{
		i++;
		tok = tok->next;
	}
	if (!i)
		return (0);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tok = tokens;
	while (tok && (tok->type == ARG || tok->type == BUILTIN
			|| tok->type == CMD || tok->type == 9))
	{
		res[i++] = ft_strdup(tok->str);
		tok = tok->next;
	}
	res[i] = 0;
	return (res);
}