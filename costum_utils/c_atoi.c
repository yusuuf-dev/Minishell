#include "../minishell.h"

int	c_atoi(char *s, long *rslt)
{
	size_t	i;
	long	sign;

	i = 0;
	sign = 1;
	while ((s[i] > 8 && s[i] < 14) || s[i] == ' ') // I probably don't need this anymore since the split skips whitespaces
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
		*rslt = (*rslt) + (s[i] - 48);
		i++;
		if (((*rslt >= 9223372036854775807 && sign == 1) || (*rslt >= 9223372036854775807 && sign == -1)) && ft_isdigit(s[i]))
			return (-1);					// not good enough needs rework
	}
	*rslt = (*rslt) * sign;
	return (0);
}