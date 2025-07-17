/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:04:00 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/17 15:24:07 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *ft_strdup_env(char *s)
{
        size_t  i;
        char    *p;

        i = 0;
        if (!s)
                return (NULL);
        p = ft_malloc_env(ft_strlen(s) + 1);
        while (s[i])
        {
                p[i] = s[i];
                i++;
        }
        p[i] = 0;
        return (p);
}