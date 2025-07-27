/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_strncmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:06:22 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/15 18:07:32 by asoufian         ###   ########.fr       */
=======
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:06:22 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/26 09:24:47 by yoel-you         ###   ########.fr       */
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
int     c_strncmp(const char *s1, const char *s2)
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
=======
int	c_strncmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] != '=')
	{
		if (s1[i] - s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (!(s2[i]))
		return (0);
	return (s1[i] - s2[i]);
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
}
