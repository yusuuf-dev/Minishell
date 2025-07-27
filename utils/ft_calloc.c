/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:40:14 by yoel-you          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/22 11:29:55 by yoel-you         ###   ########.fr       */
=======
/*   Updated: 2025/07/26 10:57:59 by yoel-you         ###   ########.fr       */
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t n)
{
	void	*p;

	p = ft_malloc(n);
	memset(p, 0, n);
<<<<<<< HEAD
	/*n--;
	while (n)
	{
		p[n] = 0;
		n--;
	}
	p[n] = 0;*/
	return (p);
}
=======
	return (p);
}
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
