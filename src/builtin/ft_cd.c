/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:59:53 by abasarud          #+#    #+#             */
/*   Updated: 2023/05/26 18:07:38 by abasarud         ###   ########.fr       */
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
#include <string.h>
int	cd(int argc, char **argv, Node* envListHead)
{
		(void) argc;
	 char *old_pwd[] = {"OLDPWD", "OLDPWD", "OLDPWD"};
	 char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
{
		deleteNode(&envListHead, &old_pwd[0]);
		insertNode(&envListHead, *old_pwd, cwd);
}
else 
printf("error\n");
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
		// deleteNode(&mini->envListHead, &old_pwd);
		// insertNode(&mini->envListHead, old_pwd, now);
		chdir(argv[1]);
		char curr[1024];
		char *pwd[] = {"PWD", "PWD"};
    if (getcwd(curr, sizeof(curr)) != NULL)
{

		deleteNode(&envListHead, &pwd[0]);
		insertNode(&envListHead, *pwd, curr);
}

	// }
	return (0);
}
