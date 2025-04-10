/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:00:27 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/10 15:05:26 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int     ft_pwd(int argc, char **argv, char **envp)
{
        char    *p;

	(void)argc;
	(void)argv;
	(void)envp;
        p = NULL;
        p = getcwd(p, 4100);
        printf("%s\n", p);
        free(p);
        return (0);
}
