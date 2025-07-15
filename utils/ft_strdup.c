/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:04:00 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/14 09:11:15 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *ft_strdup(char *s)
{
        size_t  i;
        char    *p;

        i = 0;
        if (!s)
                return (NULL);
        p = ft_malloc(ft_strlen(s) + 1);
        while (s[i])
        {
                p[i] = s[i];
                i++;
        }
        p[i] = 0;
        return (p);
}
