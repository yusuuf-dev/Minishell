/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:37:31 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/15 13:39:34 by asoufian         ###   ########.fr       */
=======
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:37:31 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/26 09:28:33 by yoel-you         ###   ########.fr       */
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *s, char **envp, unsigned char *status)
{
	size_t	i;
	char	*value;

	i = 0;
	while (envp[i])
	{
		if (!c_strncmp(envp[i], s))
		{
			value = ft_strchr(envp[i], '=');
			if (value)
				return (value + 1);
			return (NULL);
		}
		if (s[0] == '?' && !s[1])
			return (i = *status, ft_itoa(i));
		i++;
	}
	return (NULL);
}
