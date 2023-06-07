/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:17:23 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/07 13:23:47 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define _XOPEN_SOURCE 600

#define BUFFER_SIZE 1024
#define TMP_FILE	"kaka.txt"
#define IN	0
#define OUT	1

void	redirect_or_print(t_mini *mini, t_token *next_command, int save_fd_out)
{
	int	null_fd;

	if (next_command && next_command->type == APPEND && next_command->next)
		redirect_output(mini, next_command->next, next_command->type);
	else if (next_command == NULL)
	{
		make_tmp_file_input();
		dup2(save_fd_out, STDOUT_FILENO);
		close(save_fd_out);
	}
	else
	{
		null_fd = open("/dev/null", O_CREAT | O_WRONLY);
		dup2(null_fd, STDOUT_FILENO);
		close(null_fd);
		make_tmp_file_trunc(next_command->next->str);
	}
}

void	here_doc_input(t_mini *mini, t_token *command, int pid)
{
	int		tmp_fd;
	int		save_fd_out;
	int		status;
	int		save_fd[2];
	char	**eof;

	eof = convert_argv(command);
	tmp_fd = create_temporary_file();
	if (tmp_fd == -1)
		return ;
	save_fd_out = dup(OUT);
	dup2(save_fd[OUT], STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		get_and_write_input(tmp_fd, *eof);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		clear_tmp_file_input();
	make_tmp_file_input();
	redirect_or_print(mini, command->next, save_fd_out);
}
