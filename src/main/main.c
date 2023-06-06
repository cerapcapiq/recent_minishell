/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:18:36 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/06 16:09:34 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_main(int argc, char **argv)
{
	if (argc > 1 || argv[1])
	{
		printf("one argc ./minishell ");
		exit(1);
	}
}

char	*display_readline(char *input)
{
	input = readline("@minishell> ");
	return (input);
}

int	ft_whitespace(char *input)
{
	if (input == NULL)
		return (0);
	while (*input == '\t' || *input == ' ' )
		input++;
	if (*input == '\0')
		return (1);
	return (0);
}

static void	read_input(t_mini *mini, char *input)
{
	input = readline("@minishell> ");
	if (!ft_whitespace(input))
	{
		parse(mini, input);
		add_history(input);
		dup2(mini->stdin, STDIN_FILENO);
		dup2(mini->stdout, STDOUT_FILENO);
	}
	free(input);
}

int	main(int ac, char *av[], char *envp[])
{
	t_mini	*mini;
	char	*input;

	g_exit_num = 0;
	define_signal();
	init_main(ac, av);
	mini = init_mini();
	mini->var_list = var_initialize_var();
	mini->env_list = get_terminal_env_list(envp);
	while (1)
	{
		input = NULL;
		read_input(mini, input);
	}
	free_head(mini->env_list);
	free_var(mini->var_list);
	return (mini->execute_code);
}
