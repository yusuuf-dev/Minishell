/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:29:28 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 18:51:05 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_list(t_lstm **lst)
{
	t_lstm	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->p);
		free(tmp);
	}
	*lst = NULL;
}

/* move the below and above function into ft_free.c */
static void	free_all_malloc(t_lstm **lstm, t_lstm **lstm_env, int isfailed)
{
	if (*lstm_env)
	{
		free_list(lstm_env);
	}
	if (*lstm)
	{
		free_list(lstm);
	}
	if (isfailed)
	{
		close_dup_fds();
		write(2, "failed malloc\n", 14);
		exit(1);
	}
}

static void	add_malloc(t_lstm *new, t_lstm **lstm, int get_env)
{
	t_lstm	*tmp;

	if (*lstm)
	{
		tmp = *lstm;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
	else
	{
		*lstm = new;
		if (get_env)
			envp_head_of_ft_malloc_struct(*lstm);
		else
			head_of_ft_malloc_struct(*lstm);
	}
}

static void	new_malloc(void *ptr, t_lstm **lstm, t_lstm **lstm_env, int is_env)
{
	t_lstm	*new;

	new = malloc(sizeof(t_lstm));
	if (!new)
	{
		free(ptr);
		free_all_malloc(lstm, lstm_env, 1);
	}
	new->p = ptr;
	new->next = NULL;
	if (is_env)
	{
		add_malloc(new, lstm_env, 1);
	}
	else
		add_malloc(new, lstm, 0);
}

void	config_malloc(void *ptr, int isfailed, int is_env)
{
	static t_lstm	*lstm = NULL;
	static t_lstm	*lstm_env = NULL;

	if (!ptr)
	{
		if (is_env == 2 && isfailed == 0)
		{
			close_dup_fds();
			free_all_malloc(&lstm, &lstm_env, 0);
			return ;
		}
		if (isfailed == 1)
			free_all_malloc(&lstm, &lstm_env, 1);
		if (isfailed == 0 && is_env == 0)
			free_list(&lstm);
		if (isfailed == 0 && is_env == 1)
			free_list(&lstm_env);
	}
	else
		new_malloc(ptr, &lstm, &lstm_env, is_env);
}
