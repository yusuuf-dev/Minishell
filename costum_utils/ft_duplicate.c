/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duplicate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:17:28 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/15 10:17:29 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_duplicate(char	**s, size_t add_size)
{
	size_t	i;
	size_t	size;
	char	**p;

	i = size = 0;
	while (s[size])
		size++;
	size = (sizeof(char *) * (size + 1 + add_size));
	p = ft_malloc_env(size);
	memset(p, 0, size);
	if (!p)
		exit (-1);
	while (s[i])
	{
		p[i] = ft_strdup_env(s[i]);
		i++;
	}	
	return (p);
}
