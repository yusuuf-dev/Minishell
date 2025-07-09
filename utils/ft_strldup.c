/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:12:29 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/09 12:30:14 by yoel-you         ###   ########.fr       */
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
                p = malloc(n + 1);
        else
                p = malloc(len + 1);
        while (s[i] && i < n)
        {
                p[i] = s[i];
                i++;
        }
        p[i] = 0;
        return (p);
}
