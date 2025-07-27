<<<<<<< HEAD
#include "../minishell.h"
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:04 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/19 10:36:25 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
char	*ft_substr_c(char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (!s || (len - start) == 0)
		return (NULL);
	i = 0;
	p = ft_malloc(len - start + 1);
	while ((start + i) < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
<<<<<<< HEAD
}
=======
}
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
