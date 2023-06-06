/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:14:52 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/06 16:11:17 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//ctrl c = sigint (intrrup process) ---> new prompt  || done!
//ctrl \ = sigquit (quit process) ---->nothing   |||done!
//ctrl z = sigstp ()
//ctrl d = eof --> exit || done!

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

void	sig_handler(int signum)
{
	printf("%d done", signum);
}

//__attribute__((unused))
void	int_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	disable_veof(void)
{
	struct termios	ori_settings;
	struct termios	new_settings;
	bool			echo_ctl_chr;

	tcgetattr(STDIN_FILENO, &ori_settings);
	new_settings = ori_settings;
	new_settings.c_cc[VEOF] = 4;
	new_settings.c_cc[VINTR] = 3;
	echo_ctl_chr = false;
	if (echo_ctl_chr)
		new_settings.c_lflag |= ECHOCTL;
	else
		new_settings.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

void	define_signal(void)
{
	disable_veof();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, int_handler);
}
