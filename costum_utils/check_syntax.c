/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:19:15 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/22 20:30:54 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_next(char *p, int index, int isdouble)
{
	int	i;

	if (isdouble)
		i = index + 2;
	else
		i = index + 1;
	while (p[i] && p[i] == ' ')
		i++;
	if (p[index] == '|' && (!p[i] || p[i] == '|'))
		return (ft_putstr("Minishell: syntax error\n", 2), 1);
	if (p[index] == '|')
		return (0);
	if (!p[i] || p[i] == '<' || p[i] == '>' || p[i] == '|')
		return (ft_putstr("Minishell: syntax error\n", 2), 1);
	return (0);
}

static void	ft_space(char *p)
{
	int		i;
	char	q;

	i = 0;
	q = 0;
	while (p[i])
	{
		if (!q && (p[i] == '\'' || p[i] == '\"'))
			q = p[i];
		else if (q && p[i] == q)
			q = 0;
		else if (p[i] >= 9 && p[i] <= 13)
			p[i] = ' ';
		i++;
	}
}

static int	is_onlyspace(char *p)
{
	int	i;

	ft_space(p);
	i = 0;
	while (p[i])
	{
		if (p[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	check_operator(char *p, int i)
{
	if (p[i] == '|' && check_next(p, i, 0))
		return (1);
	if (p[i] == '>' && p[i + 1] == '>' && check_next(p, i, 1))
		return (1);
	if (p[i] == '<' && p[i + 1] == '<' && check_next(p, i, 1))
		return (1);
	if (p[i] == '>' && p[i + 1] != '>' && check_next(p, i, 0))
		return (1);
	if (p[i] == '<' && p[i + 1] != '<' && check_next(p, i, 0))
		return (1);
	return (0);
}

int	check_syntax(t_data *data)
{
	int		i;
	char	q;

	i = 0;
	q = 0;
	if (is_onlyspace(data->p_rdl))
		return (1);
	add_history(data->p_rdl);
	if (found_quotes(data->p_rdl) == -1)
		return (ft_putstr("Error Unclose quote\n", 2), data->status = 2, 1);
	while (data->p_rdl[i] == ' ')
		i++;
	if (data->p_rdl[i] == '|')
		return (ft_putstr("Minishell: syntax error\n", 2), data->status = 2, 1);
	while (data->p_rdl[i])
	{
		if (!q && (data->p_rdl[i] == '\'' || data->p_rdl[i] == '\"'))
			q = data->p_rdl[i];
		else if (q && data->p_rdl[i] == q)
			q = 0;
		else if (!q && check_operator(data->p_rdl, i))
			return (data->status = 2, 1);
		i++;
	}
	return (0);
}
