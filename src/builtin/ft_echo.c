/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:00:06 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/31 19:43:10 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	print_echo_args(char **argv, int start)
{
	int	i;

	i = start;
	while (argv[i])
	{
		if (closed_quote(argv[i]) || closed_dub_quote(argv[i]))
			argv[i] = ft_delete_quote(argv[i]);
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
}

void	checkinsidestruct(t_node *env_list2, t_var *env_list, char *name)
{
	char	*value;

	value = var_get_env_value(env_list, name);
	if (value != NULL)
	{
		printf("%s", value);
		return ;
	}
	value = get_env_value(env_list2, name);
	if (value != NULL)
	{
		printf("%s", value);
		return ;
	}
	if (value == NULL)
		printf("%s", name);
	return ;
}

int	echo(int argc, char **argv, t_token curr, t_mini *mini)
{
	int	i;
	int	flag;

	if (argc < 2)
		return (1);
	i = 1;
	flag = 0;
	if (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	if (curr.quote != 1)
	{
		argv[i] = ft_strremove(argv[i], "$");
		checkinsidestruct(mini->env_list, mini->var_list, argv[i]);
	}
	else
		print_echo_args(argv, i);
	if (flag == 0)
		printf("\n");
	return (0);
}
