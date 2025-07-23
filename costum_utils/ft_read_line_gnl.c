/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line_gnl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:43:31 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/23 09:43:32 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *ft_read_line_gnl(int p_prompt)
{
    char    *line;
    char    *tmp;
    char    *p_rdl;

    if  (isatty(STDIN_FILENO))
    {
        if (p_prompt)
		    tmp = readline("minishell : ");
        else
            tmp = readline("> ");
        p_rdl = ft_strdup(tmp);
        free(tmp);
    }
	else
	{
		line = get_next_line(STDIN_FILENO);
        if (line && line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = 0;
		p_rdl = line;
	}
    return (p_rdl);
}
