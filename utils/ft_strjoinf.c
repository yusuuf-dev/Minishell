/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:05:57 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/11 10:58:47 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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