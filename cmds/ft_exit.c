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
int	ft_exit(t_data *data)
{
//	size_t	i = 0;
	long	ret = 0;
	unsigned char c;

	data->exit = 1;
	if (!data->rdl_args[1])
		return 1;
	if (!ft_valid_int(data->rdl_args[1]))
		return (ft_putstr("minishell: exit: ", 2), ft_putstr(data->rdl_args[1], 2), ft_putstr(": numeric argument required\n", 2), 2);
	if (data->rdl_args[2] != NULL)
		return (ft_putstr("exit\nminishell: exit: too many arguments\n", 2), data->exit = 0, 1);
	
	if (ft_valid_int(data->rdl_args[1]))
	{
		//ret = ft_atoi(argv[1], &ret);
		if (c_atoi(data->rdl_args[1], &ret) == -1)
		{
			printf("minishell: exit: %s: numeric argument required\n", data->rdl_args[1]);
			return (2);
		}
		return(c = ret, c);
	}
	printf("minishell: exit: %s: numeric argument required\n", data->rdl_args[1]);
	return(2);
}