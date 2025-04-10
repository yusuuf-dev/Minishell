/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:04:00 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/10 14:05:39 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

size_t  ft_strlen(char *s)
{
        size_t  i;

        if (!s)
                return (0);
        i = 0;
        while (s[i])
                i++;
        return (i);
}

int     ft_strcmp(const char *s1, const char *s2, size_t n)
{
        size_t  i;

        i = 0;
        if (!s1 || !s2)
                exit(-1);
        while(s1[i] && i < n)
        {
                if (s1[i] - s2[i])
                        return (s1[i] - s2[i]);
                i++;
        }
        i--;
        return (s1[i] - s2[i]);
}

char    *ft_strchr(char *s, char c)
{
        size_t  i;

        i = 0;
        if (!s)
                return (NULL);
        while (s[i])
        {
                if (s[i] == c)
                        return (s + i);
                i++;
        }
        return (NULL);
}

