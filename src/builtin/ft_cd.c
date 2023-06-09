/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:59:53 by abasarud          #+#    #+#             */
/*   Updated: 2023/06/01 13:17:10 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static int	cd_too_many_arguments(void)
{
	printf("minishell: cd: too many arguments\n");
	return (1);
}

static void	update_old_pwd(t_node **env_list)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		delete_node(env_list, (char *[]){"OLDPWD", "OLDPWD" });
		insert_node(env_list, "OLDPWD", cwd);
	}
	else
	{
		printf("error\n");
	}
}

static int	update_pwd(t_node **env_list)
{
	char	curr[1024];

	if (getcwd(curr, sizeof(curr)) != NULL)
	{
		delete_node(env_list, (char *[]){"PWD", "PWD"});
		insert_node(env_list, "PWD", curr);
		return (0);
	}
	return (1);
}

int	cd(int argc, char **argv, t_node **env_list)
{
	int	exit_status;

	if (argc > 2)
		return (cd_too_many_arguments());
	update_old_pwd(env_list);
	exit_status = chdir(argv[1]);
	if (exit_status != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", argv[1]);
		return (1);
	}
	return (update_pwd(env_list));
}
