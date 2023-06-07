/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:07:33 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/07 13:37:13 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define _XOPEN_SOURCE 600

#define BUFFER_SIZE 1024
#define TMP_FILE	"kaka.txt"
#define IN	0
#define OUT	1

int	create_temporary_file(void)
{
	int	fd;

	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		printf("error\n");
	return (fd);
}

void	get_and_write_input(int tmp_fd, char *eof)
{
	char	*input;

	while (true)
	{
		input = readline("> ");
		if (!input)
		{
			printf("warning,");
			close(tmp_fd);
			exit(0);
		}
		if (ft_strcmp(input, eof))
			ft_putendl_fd(input, tmp_fd);
		else
		{
			close(tmp_fd);
			free(input);
			break ;
		}
		free(input);
	}
	exit(0);
}

void	clear_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_WRONLY, 0600);
	close(tmp_fd);
}

void	make_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_RDONLY);
	dup2(tmp_fd, IN);
	close(tmp_fd);
}

#define BUFFER_SIZE 1024

void	make_tmp_file_trunc(char *str)
{
	int		tmp_fd;
	int		temp;
	int		dest;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes;

	tmp_fd = open("kaka.txt", O_RDONLY);
	dest = open(str, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (tmp_fd == -1 || dest == -1)
	{
		printf("Failed to open the files.\n");
		return ;
	}
	bytes = read(tmp_fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		temp = bytes;
		write(dest, buffer, temp);
		bytes = read(tmp_fd, buffer, BUFFER_SIZE);
	}
	close(tmp_fd);
	close(dest);
}
