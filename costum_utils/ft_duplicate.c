/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duplicate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:17:28 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/28 11:18:13 by yoel-you         ###   ########.fr       */
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
	size = (sizeof(char *) * (size + 1));
	p = ft_malloc_env(size);
	ft_memset(p, 0, size);
	while (s[i])
	{
		p[i] = ft_strdup_env(s[i]);
		i++;
	}
	return (p);
}
