/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duplicate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:17:28 by yoel-you          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/22 12:05:47 by yoel-you         ###   ########.fr       */
=======
/*   Updated: 2025/07/26 11:45:02 by yoel-you         ###   ########.fr       */
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_duplicate(char **s)
{
	size_t	i;
	size_t	size;
	char	**p;

	i = 0;
	size = 0;
	while (s[size])
		size++;
<<<<<<< HEAD
	size = (sizeof(char *) * (size + 1 + add_size));
	p = ft_malloc_env(size);
	memset(p, 0, size);
	if (!p)
		exit (-1);
=======
	size = (sizeof(char *) * (size + 1));
	p = ft_malloc_env(size);
	memset(p, 0, size);
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	while (s[i])
	{
		p[i] = ft_strdup_env(s[i]);
		i++;
	}
	return (p);
}
