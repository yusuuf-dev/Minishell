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

static void ft_strcpy(char *dest, char *src)
{
	size_t	i = 0;

	while(src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}

static char	*ft_itoa(int n)
{
	char	*s = ft_calloc(17);
	int		i = 15;

	if (!n)
		return (s[0] = '0', s);
	while (n)
	{
		s[i] = (n % 10) + '0';
		i--;
		n = n / 10;
	}
	ft_strcpy(s, (s + i + 1));
	return (s);
}

static int     c_strncmp(const char *s1, const char *s2) // there's another copy of this in ft_export
{
    size_t  i;

    i = 0;
    while(s1[i] && s1[i] != '=')
    {
        if (s1[i] - s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
	if (!(s2[i]))
		return (0);
    return (s1[i] - s2[i]);
}

char	*ft_getenv(char *s, char **envp, unsigned char *status)
{
	size_t	i = 0;
	// size_t	size = 0;

	// size = ft_strlen(s);
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
