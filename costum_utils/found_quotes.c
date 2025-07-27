/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:04:54 by yoel-you          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/20 18:11:36 by yoel-you         ###   ########.fr       */
=======
/*   Updated: 2025/07/23 09:41:08 by yoel-you         ###   ########.fr       */
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	found_quotes(char *s)
{
<<<<<<< HEAD
    int     empty;
    int     quotes;
	size_t	i;
    char    q;

	i = 0;
    q = 0;
    empty = 0;
    quotes = 0;
	while (s[i])
	{
        if (!q && (s[i] == '\'' || s[i] == '\"'))
        {
            q = s[i];
            quotes = 1;
        }
        else if (q && s[i] == q)
            q = 0;
        if ((!q && s[i] != q && quotes) || (!q && s[i]))
            empty = 1;
		i++;
	}
    if(q)
    {
        return(-1);
    }
	return(quotes + empty);
=======
	int		empty;
	int		quotes;
	size_t	i;
	char	q;

	i = 0;
	q = 0;
	empty = 0;
	quotes = 0;
	while (s[i])
	{
		if (!q && (s[i] == '\'' || s[i] == '\"'))
		{
			q = s[i];
			quotes = 1;
		}
		else if (q && s[i] == q)
			q = 0;
		if ((!q && s[i] != q && quotes) || (!q && s[i]))
			empty = 1;
		i++;
	}
	if (q)
		return (-1);
	return (quotes + empty);
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
}
