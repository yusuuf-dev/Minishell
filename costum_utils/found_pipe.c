/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:25:07 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 09:25:08 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
int found_pipe(char *line)
{
    size_t  i;
    char    q;

    i = 0;
    q = 0;
    while (line[i])
    {
        if (!q && (line[i] == '\'' || line[i] == '\"'))
            q = line[i];
        else if (line[i] == q)
            q = 0;
        else if (!q && line[i] == '|')
            return (1);
        i++;
    }
    return (0);
=======
int	found_pipe(char *line)
{
	size_t	i;
	char	q;

	i = 0;
	q = 0;
	while (line[i])
	{
		if (!q && (line[i] == '\'' || line[i] == '\"'))
			q = line[i];
		else if (line[i] == q)
			q = 0;
		else if (!q && line[i] == '|')
			return (1);
		i++;
	}
	return (0);
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
}
