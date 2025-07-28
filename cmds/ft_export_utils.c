/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:22:39 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/24 14:44:17 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_ex_strncmp(const char *s1, const char *s2, char terminator)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		exit(-1);
	while (s1[i])
	{
		if (s1[i] == terminator && s2[i] != terminator)
			return (-1);
		if (s2[i] == terminator && s1[i] != terminator)
			return (1);
		if (s1[i] - s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	i--;
	return (s1[i] - s2[i]);
}

static void	ft_putstr_quote(char *s)
{
	size_t	i;
	int		found;

	i = 0;
	found = 0;
	while (s[i])
	{
		if (!found && s[i] == '=')
		{
			write(1, &s[i], 1);
			write(1, "\"", 1);
			found = 1;
		}
		else
			write(1, &s[i], 1);
		i++;
	}
	if (found)
		write(1, "\"", 1);
	write(1, "\n", 1);
}

static void	print_the_envs(char **envp, int *sorted)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp && envp[i])
	{
		j = 0;
		while (sorted[j] != (i + 1))
			j++;
		ft_putstr("declare -x ", 1);
		ft_putstr_quote(envp[j]);
		i++;
	}
}

void	print_env(char **envp, int i, int j, int smallest)
{
	int		*sorted;

	while (envp && envp[j])
		j++;
	sorted = ft_calloc((j) * sizeof(int));
	while (envp && envp[i])
	{
		j = 0;
		smallest = 0;
		while (sorted[smallest])
			smallest++;
		while (envp[j])
		{
			if (!(sorted[j]) && (ft_ex_strncmp(envp[j],
						envp[smallest], '=') < 0))
				smallest = j;
			j++;
		}
		sorted[smallest] = i + 1;
		i++;
	}
	print_the_envs(envp, sorted);
}
