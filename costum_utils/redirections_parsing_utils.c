/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parsing_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:23:44 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/23 11:50:20 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ambiguous(t_data *data)
{
	t_redi_lst	*tmp;

	tmp = data->redi_lst;
	while (tmp)
	{
		if (tmp->file_name == NULL && tmp->redi_type != REDI_HEREDOC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	found_redi(char c1, char c2)
{
	if (c1 == '>' && c2 != '>')
		return (REDI_OUT);
	else if (c1 == '<' && c2 != '<')
		return (REDI_IN);
	else if (c1 == '>' && c2 == '>')
		return (REDI_APPEND);
	else if (c1 == '<' && c2 == '<')
		return (REDI_HEREDOC);
	else
		return (-1);
}

void	add_linkedlist(t_data *data, t_redi_lst *new)
{
	t_redi_lst	*tmp;

	if (!data->redi_lst)
	{
		data->redi_lst = new;
		return ;
	}
	tmp = data->redi_lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	add_list_redi(t_data *data, int type, int fd, char *name)
{
	t_redi_lst	*new_redi;

	new_redi = ft_calloc(sizeof(t_redi_lst));
	new_redi->redi_type = type;
	if (type == REDI_OUT || type == REDI_APPEND)
	{
		if (fd == -1)
			new_redi->fd = 1;
	}
	if (fd != -1)
		new_redi->fd = fd;
	new_redi->file_name = name;
	add_linkedlist(data, new_redi);
}
