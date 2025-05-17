/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:38:07 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/13 11:00:24 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(int	c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_valid_int(char *s)
{
	size_t	i = 0;

	if (!ft_isdigit(s[i]) && s[i] != '-' && s[i] != '+')
		return (0);
	i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}
int	ft_exit(char **argv, char **envp)
{
//	size_t	i = 0;
	long	ret = 0;
	unsigned char c;
	(void)envp;

	if (!argv[1])
		return (0);
	if (!ft_valid_int(argv[1]))
		return (ft_putstr("minishell: exit: ", 2), ft_putstr(argv[1], 2), ft_putstr(": numeric argument required\n", 2), 2);
	if (argv[2] != NULL)
		return (ft_putstr("exit\nminishell: exit: too many arguments\n", 2), 1);
	
	if (ft_valid_int(argv[1]))
	{
		//ret = ft_atoi(argv[1], &ret);
		if (c_atoi(argv[1], &ret) == -1)
		{
			printf("minishell: exit: %s: numeric argument required\n", argv[1]);
			return (2);
		}
		return(c = ret, c);
	}
	printf("minishell: exit: %s: numeric argument required\n", argv[1]);
	return(2);
}