/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:18:36 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 16:11:09 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_mini	*init_mini(void)
{
	t_mini	*mini;

	mini = (t_mini *)malloc(sizeof(t_mini));
	mini->tokens = 0;
	mini->cmd = 1;
	mini->pipe_read = -1;
	mini->pipe_write = -1;
	mini->input = -1;
	mini->output = -1;
	mini->stdin = dup(STDIN_FILENO);
	mini->stdout = dup(STDOUT_FILENO);
	mini->execute_code = 0;
	mini->env = NULL;
	mini->env_list = NULL;
	mini->var_list = NULL;
	return (mini);
}

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
	input = display_readline(input);
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
