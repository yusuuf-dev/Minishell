/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:12:29 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/14 09:12:41 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *ft_strldup(char *s, size_t     n)
{
        size_t  i;
        size_t  len;
        char    *p;

        i = 0;
        if (!s)
                return (NULL);
        len = ft_strlen(s);
        if (n <= len)
                p = ft_malloc(n + 1);
        else
                p = ft_malloc(len + 1);
        while (s[i] && i < n)
        {
                p[i] = s[i];
                i++;
        }
        p[i] = 0;
        return (p);
}
