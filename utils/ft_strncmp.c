/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:04:46 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/14 09:07:46 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		exit(-1);
	while (s1[i] && i < n)
	{
		if (s1[i] - s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	i--;
	return (s1[i] - s2[i]);
}
