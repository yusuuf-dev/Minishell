<<<<<<< HEAD
#include "../minishell.h"

void *ft_malloc(size_t size)
{
    void *p;

    p = malloc(size);
    if (!p)
        config_malloc(NULL,1,0);
    else
    {
        config_malloc(p, 0,0);
    }
    return (p);
}

void *ft_malloc_env(size_t size)
{
    void *p;

    p = malloc(size);
    if (!p)
        config_malloc(NULL,1,1);
    else
    {
        config_malloc(p, 0, 1);
    }
    return (p);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:29:10 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 09:29:11 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_malloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		config_malloc(NULL, 1, 0);
	else
	{
		config_malloc(p, 0, 0);
	}
	return (p);
}

void	*ft_malloc_env(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		config_malloc(NULL, 1, 1);
	else
	{
		config_malloc(p, 0, 1);
	}
	return (p);
}
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
