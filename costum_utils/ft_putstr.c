/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:43:24 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/23 09:43:25 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *s, int fd)
{
<<<<<<< HEAD
    if (!s)
        return;
    write(fd, s, ft_strlen(s));
}
=======
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
