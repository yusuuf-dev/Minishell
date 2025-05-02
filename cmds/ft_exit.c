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
int	ft_exit(int argc, char **argv, char **envp)
{
//	size_t	i = 0;
	long	ret = 0;
	unsigned char c;
	(void)argc;
	(void)envp;
	if (argv[2] != NULL)
	{
		printf("too many arguments\n");
		return (2);
	}
	
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
