/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:05:57 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/10 14:16:25 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_strjoinf(char *s1, char *s2)
{
        size_t  i;
        size_t  t;
        char    *p;

        i = 0;
        t = 0;
        if (!s1)
                return (ft_strdup(s2));
        if (!s2)
                return (ft_strdup(s1));
        p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
        while (s1[i])
        {
                p[i] = s1[i];
                i++;
        }
        while(s2[t])
        {
                p[t + i] = s2[t];
                t++;
        }
        p[t + i] = 0;
        free(s1);
        return (p);
}
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

char    *ft_strdup(char *s)
{
        size_t  i;
        char    *p;

        i = 0;
        if (!s)
                return (NULL);
        p = malloc(ft_strlen(s) + 1);
        while (s[i])
        {
                p[i] = s[i];
                i++;
        }
        p[i] = 0;
        return (p);
}

