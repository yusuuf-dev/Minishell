/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_strncmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:06:22 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/15 18:07:32 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     c_strncmp(const char *s1, const char *s2)
{
    size_t  i;

    i = 0;
    while(s1[i] && s1[i] != '=')
    {
        if (s1[i] - s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
	if (!(s2[i]))
		return (0);
    return (s1[i] - s2[i]);
}
