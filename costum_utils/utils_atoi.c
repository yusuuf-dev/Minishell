/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:34:28 by yoel-you          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/23 11:38:24 by yoel-you         ###   ########.fr       */
=======
/*   Updated: 2025/07/26 10:57:26 by yoel-you         ###   ########.fr       */
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_atoi(char *s, long *rslt)
{
	size_t	i;
	long	sign;

	i = 0;
	sign = 1;
<<<<<<< HEAD
	while ((s[i] > 8 && s[i] < 14) || s[i] == ' ')
		// I probably don't need this anymore since the split skips whitespaces
=======
	while (s[i] == ' ')
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
		i++;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] >= 48 && s[i] <= 57)
	{
		if ((*rslt >= 922337203685477580 && s[i] > '7' && sign == 1))
			return (-1);
		if ((*rslt >= 922337203685477580 && s[i] > '8' && sign == -1))
			return (-1);
		*rslt = (*rslt) * 10;
<<<<<<< HEAD
		*rslt = (*rslt) + (s[i] - 48);
		i++;
		if (((*rslt >= 9223372036854775807 && sign == 1)
				|| (*rslt >= 9223372036854775807 && sign == -1))
			&& ft_isdigit(s[i]))
			return (-1); // not good enough needs rework
=======
		*rslt = (*rslt) + (s[i++] - 48);
		if (((*rslt >= LONG_MAX && sign == 1) || (*rslt >= LONG_MAX && sign
					== -1)) && ft_isdigit(s[i]))
			return (-1);
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	}
	*rslt = (*rslt) * sign;
	return (0);
}

int	redi_atoi(char *nptr)
{
	int		i;
	long	rslt;

	i = 0;
	rslt = 0;
	if (!nptr || !nptr[0])
		return (-1);
	while (nptr[i])
	{
		if (ft_isdigit(nptr[i]))
		{
			if (rslt > 2147483647)
<<<<<<< HEAD
				return (-1); // the return (used to be '2');
=======
				return (-1);
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
			rslt = rslt * 10;
			rslt = rslt + (nptr[i] - 48);
		}
		else
<<<<<<< HEAD
			return (-1); // the return (used to be '2');
=======
			return (-1);
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
		i++;
	}
	if (rslt > 2147483647)
		return (-1);
	return (rslt);
}
