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

int	ft_exit(char **argv, char **envp, unsigned char *status, int *s_exit)
{
	long	ret = 0;
	unsigned char c;
	(void)envp;

	*s_exit = 1;
	if (!argv[1])
		return (*status);
	if (!ft_valid_int(argv[1]))
		return (ft_putstr("minishell: exit: ", 2), ft_putstr(argv[1], 2), ft_putstr(": numeric argument required\n", 2), 2);
	if (argv[2] != NULL)
		return (ft_putstr("exit\nminishell: exit: too many arguments\n", 2), *s_exit = 0, 1);
	
	if (ft_valid_int(argv[1]))
	{
		if (c_atoi(argv[1], &ret) == -1)
		{
			return (ft_putstr("exit\n", 2), ft_putstr("minishell: exit: ", 2), ft_putstr(argv[1], 2), ft_putstr(": numeric argument required\n", 2), 2);
		}
		return(c = ret, c);
	}
	printf("minishell: exit: %s: numeric argument required\n", argv[1]);
	return(2);
}