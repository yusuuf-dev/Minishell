/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:05:34 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/13 10:55:57 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     ft_cd(int argc, char **argv, char **envp)
{

    (void)argc;
	(void)envp;
	if (!argv[1])
	{
		if (chdir(ft_getenv("HOME", envp)))
		{
			perror("cd");
			return (errno);
		}
		else 
			return (0);
	}
    if (argv[2] != NULL)
	{
		perror("cd");
		return (errno);
	}
	else if (argv[1][0] == '-' && !argv[1][1])	
	{		
		if (chdir(ft_getenv("OLDPWD", envp))) // the OLDPWD variabe doesn't change unlik in bash;	
		{
			perror("cd");
			return (errno);
		}
		else 
			return (0);
		
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
