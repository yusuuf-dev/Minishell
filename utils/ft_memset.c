<<<<<<< HEAD
#include "../minishell.h"

void *ft_memset(void *ptr, int c, size_t n)
{
    size_t  i;

    i = 0;
    while (i < n)
    {
        ((unsigned char*)ptr)[i] = c;
        i++;
    }
    return (ptr);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:30 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/19 10:36:08 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *ptr, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)ptr)[i] = c;
		i++;
	}
	return (ptr);
}
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
