<<<<<<< HEAD
#include "../minishell.h"

void ft_strcpy(char *dest, char *src)
{
	size_t	i = 0;

	while(src[i])
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:17 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/19 10:36:16 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strcpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}
