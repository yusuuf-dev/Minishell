/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:05:34 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/14 11:16:46 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     ft_cd(int argc, char **argv, char **envp)
{
  //char  *old_wd = NULL;

  (void)argc;
	(void)envp;
  
//  old_wd = ft_strdup(ft_getenv("PWD", envp));

	if (!argv[1] || (argv[1][0] == '~' && !argv[1][1]))
	{
		if (chdir(ft_getenv("HOME", envp)))
		{
			perror("cd");
			return (errno);
		}
		else 
    {
     // envp = ft_export()
			return (0);
    }
	}
    if (argv[2] != NULL)
	{
		perror("cd");
		return (errno);
	}
	else if (argv[1][0] == '-' && !argv[1][1])	
	{		
		if (chdir(ft_getenv("OLDPWD", envp)))
		{
			perror("cd");
			return (errno);
		}
		else 
    {
      printf("%s\n", ft_getenv("OLDPWD", envp));
			return (0);
    }
	}
	else
	{
		if (chdir(argv[1]))
		{
			perror("cd");
			return (errno);
		}
		else 
			return (0);
	}
}
