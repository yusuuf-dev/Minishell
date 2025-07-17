/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:37:31 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/15 13:39:34 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *s, char **envp, unsigned char *status)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (!c_strncmp(envp[i], s))
		{
			return (ft_strchr(envp[i], '=') + 1);
		}
		if (s[0] == '?' && !s[1])
			return (i = *status, ft_itoa(i));
		i++;
	}
	return (NULL);
}
