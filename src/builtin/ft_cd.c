/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:59:53 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/30 16:04:08 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

// void	check_old_path(void)
// {
// 	char	**s;
// 	int		i;

// 	s = environ;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (findSubstring(s[i], "OLDPWD"))
// 			printf("%s\n [%d] \n", s[i], i);
// 		i++;
// 	}
// }

// char	*save_old_path(void)
// {
// 	char	*s;

// 	s = ft_var_content("OLDPWD", head_ref);
// 	return (s);
// }
// (void) mini;
	// if (ft_strcmp(argv[1], "-"))
	// {
	// 	now = getcwd(arg, 1024);
	// 	curr = save_old_path();
	// }
	// if (!ft_strcmp(argv[1], "~"))
	// {
	// 	ft_home_dir();
	// 	return (0);
	// }
	// if (!ft_strcmp(argv[1], "-"))
	// {
	// 	ft_prev_dir(now);
	// 	return (0);
	// }
	// else
	// {
		// char *now = getcwd(*argv, 1024);
		// char *old_pwd = "OLDPWD";
		// printf("now is %s", now);
		// printf("old path %s", old_pwd);
		// deletet_node(&mini->env_list, &old_pwd);
		// insertt_node(&mini->env_list, old_pwd, now);

int	cd(int argc, char **argv, t_node *env_list)
{
	char	**old_pwd;
	char	*cwd;
	char	curr[1024];
	char	**pwd;

	old_pwd = (char *[]){"OLDPWD", "OLDPWD"};
	pwd = (char *[]){"PWD", "PWD"};
	(void) argc;
	cwd = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		delete_node(&env_list, &old_pwd[0]);
		insert_node(&env_list, *old_pwd, cwd);
	}
	else
		printf("error\n");
	chdir(argv[1]);
	if (getcwd(curr, sizeof(curr)) != NULL)
	{
		delete_node(&env_list, &pwd[0]);
		insert_node(&env_list, *pwd, curr);
	}
	return (0);
}
