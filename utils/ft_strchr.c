/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:04:02 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/14 09:07:26 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
