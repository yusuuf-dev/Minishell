/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:34:28 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 10:57:26 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_atoi(char *s, long *rslt)
{
	size_t	i;
	long	sign;

	i = 0;
	sign = 1;
	while (s[i] == ' ')
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
		*rslt = (*rslt) + (s[i++] - 48);
		if (((*rslt >= LONG_MAX && sign == 1) || (*rslt >= LONG_MAX && sign
					== -1)) && ft_isdigit(s[i]))
			return (-1);
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
				return (-1);
			rslt = rslt * 10;
			rslt = rslt + (nptr[i] - 48);
		}
		else
			return (-1);
		i++;
	}
	if (rslt > 2147483647)
		return (-1);
	return (rslt);
}
