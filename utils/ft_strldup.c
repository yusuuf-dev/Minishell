/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:12:29 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/14 18:57:05 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strldup(char *s, size_t n)
{
	size_t	i;
	size_t	len;
	char	*p;

<<<<<<< HEAD
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
=======
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
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
}
