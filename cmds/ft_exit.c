/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:24:06 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/26 19:11:30 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_error(char *s2)
{
	char	*s1;
	char	*s3;
	char	*str;

	str = "exit\n";
	if (isatty(STDOUT_FILENO))
		ft_putstr(str, 2);
	if (s2)
	{
		s1 = "minishell: exit: ";
		s3 = ": numeric argument required\n";
		ft_putstr(s1, 2);
		ft_putstr(s2, 2);
		ft_putstr(s3, 2);
	}
	else
	{
		ft_putstr("minishell: exit: too many arguments\n", 2);
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_valid_int(char *s)
{
	size_t	i;

	i = 0;
	while ((s[i] > 8 && s[i] < 14) || s[i] == ' ')
		i++;
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

int	ft_exit(char **argv, t_data *data)
{
	long	ret;

	ret = 0;
	if (!argv[1])
	{
		if (!data->is_a_child && isatty(STDOUT_FILENO))
			ft_putstr("exit\n", 2);
		return (1);
	}
	if (!ft_valid_int(argv[1]))
		return (print_error(argv[1]), data->status = 2, 1);
	if (argv[2] != NULL)
		return (print_error(NULL), data->status = 1, 0);
	if (ft_valid_int(argv[1]))
	{
		if (exit_atoi(argv[1], &ret) == -1)
			return (print_error(argv[1]), data->status = 2, 1);
		if (!data->is_a_child && isatty(STDOUT_FILENO))
			ft_putstr("exit\n", 2);
		return (data->status = ret, 1);
	}
	print_error(argv[1]);
	return (data->status = 2, 1);
}
