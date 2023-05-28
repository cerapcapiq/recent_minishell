/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:14:52 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/28 22:18:09 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//ctrl c = sigint (intrrup process) ---> new prompt  || done!
//ctrl \ = sigquit (quit process) ---->nothing   |||done!
//ctrl z = sigstp ()
//ctrl d = eof --> exit || done!

void	sig_handler(int signum)
{
	printf("%d done", signum);
}

static void	int_handler(int __attribute__((unused)) signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line(" ", 0);
	rl_redisplay();
}

void	disable_veof(void)
{
	struct termios	ori_settings;
	struct termios	new_settings;

	tcgetattr(STDIN_FILENO, &ori_settings);
	new_settings = ori_settings;
	new_settings.c_cc[VEOF] = 4;
	new_settings.c_cc[VINTR] = 3;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

void	define_signal(void)
{
	disable_veof();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, int_handler);
}
