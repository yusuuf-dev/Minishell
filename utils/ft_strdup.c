/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:04:00 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/14 18:57:50 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s)
{
	size_t	i;
	char	*p;

<<<<<<< HEAD
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
=======
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
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
}
