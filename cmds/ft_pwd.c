/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:23:19 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/16 11:23:20 by yoel-you         ###   ########.fr       */
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
	ft_putstr(p, 1);
	write(1, "\n", 1);
    //printf("%s\n", p);
    free(p); // this was commented, why ?
    return (0);
}