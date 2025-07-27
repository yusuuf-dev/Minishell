/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:04:00 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/14 09:11:15 by asoufian         ###   ########.fr       */
=======
/*   ft_strdup_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:04:00 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/23 09:44:07 by yoel-you         ###   ########.fr       */
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
char    *ft_strdup_env(char *s)
{
        size_t  i;
        char    *p;

        i = 0;
        if (!s)
                return (NULL);
        p = ft_malloc_env(ft_strlen(s) + 1);
        while (s[i])
        {
                p[i] = s[i];
                i++;
        }
        p[i] = 0;
        return (p);
=======
char	*ft_strdup_env(char *s)
{
	size_t	i;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	p = ft_malloc_env(ft_strlen(s) + 1);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = 0;
	return (p);
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
}
