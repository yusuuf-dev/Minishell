/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:00:27 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/21 10:06:59 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int     ft_pwd(char **argv, char **envp)
{
    char    *p;

	(void)argv;
	(void)envp;
    p = NULL;
	//p = getcwd(p, 4100);
	p = getcwd(p, 0);
	if (!p)
	{
		perror("pwd");
		return (errno);
	}
    printf("%s\n", p);
    free(p);
    return (0);
}
