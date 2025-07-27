/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:24:06 by asoufian          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/15 18:27:14 by asoufian         ###   ########.fr       */
=======
/*   Updated: 2025/07/26 19:11:30 by yoel-you         ###   ########.fr       */
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
=======
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

>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
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

<<<<<<< HEAD
int	ft_exit(char **argv, unsigned char *status, int *s_exit)
{
	long			ret;
	unsigned char	c;

	ret = 0;
	*s_exit = 1;
	if (!argv[1])
		return (*status);
	if (!ft_valid_int(argv[1]))
		return (ft_putstr("minishell: exit: ", 2), ft_putstr(argv[1], 2),
			ft_putstr(": numeric argument required\n", 2), 2);
	if (argv[2] != NULL)
		return (ft_putstr("exit\nminishell: exit: too many arguments\n", 2),
			*s_exit = 0, 1);
	if (ft_valid_int(argv[1]))
	{
		if (exit_atoi(argv[1], &ret) == -1)
		{
			ft_putstr("exit\nminishell: exit: ", 2);
			ft_putstr(argv[1], 2);
			return (ft_putstr(": numeric argument required\n", 2), 2);
		}
		return (c = ret, c);
	}
	printf("minishell: exit: %s: numeric argument required\n", argv[1]);
	return (2);
=======
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
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
}
