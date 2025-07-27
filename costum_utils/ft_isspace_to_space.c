/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace_to_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:43:56 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/26 09:28:52 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
int	 ft_isspace_to_space(char **s)
=======
int	ft_isspace_to_space(char **s)
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
{
	size_t	i;

	i = 0;
	while ((*s)[i])
	{
<<<<<<< HEAD
		// if ((*s)[i] <= 13 && (*s)[i] >= 9)
		// 	(*s)[i] = ' ';
		if ((*s)[i] != ' ' && !((*s)[i] <= 13 && (*s)[i] >= 9))
			return(0);
		i++;
	}
	return(1);
=======
		if ((*s)[i] != ' ' && !((*s)[i] <= 13 && (*s)[i] >= 9))
			return (0);
		i++;
	}
	return (1);
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
}
