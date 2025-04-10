/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:05:34 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/10 15:18:49 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_cd(int argc, char **argv, char **envp)
{

    	(void)argc;
	(void)envp;
	if (!argv[1])
	{
		if (chdir(getenv("HOME")))
		{
			printf("error while changing dir\n");
			return (-1);
		}
		else 
			return (0);
	}
    	if (argv[2] != NULL)
	{
		printf("too many arguments\n");
		return (-1);
	}	
	else
	{
		if (chdir(argv[1]))
		{
			printf("error while changing dir\n");
			return (-1);

		}
		else 
			return (0);
	}
}

