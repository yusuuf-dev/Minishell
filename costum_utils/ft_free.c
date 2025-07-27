<<<<<<< HEAD
#include "../minishell.h"

/* print the s argument using perror, frees allocated memory 
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:26:53 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 09:28:07 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* print the s argument using perror, frees allocated memory
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	exits using exit_code argument*/
void	print_free_exit(char *s, int exit_code)
{
	perror(s);
	config_malloc(NULL, 0, 2);
	exit(exit_code);
}

t_lstm	*envp_head_of_ft_malloc_struct(t_lstm *head)
{
<<<<<<< HEAD
	static t_lstm *ptr = NULL;
=======
	static t_lstm	*ptr = NULL;
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369

	if (head)
		ptr = head;
	return (ptr);
}

t_lstm	*head_of_ft_malloc_struct(t_lstm *head)
{
<<<<<<< HEAD
	static t_lstm *ptr = NULL;
=======
	static t_lstm	*ptr = NULL;
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369

	if (head)
		ptr = head;
	return (ptr);
}

<<<<<<< HEAD
static void move_content_remove_last_node(t_lstm *head)
{
	t_lstm *tmp;
	t_lstm *last_node;

	free(head->p);
	/* get the last node*/
=======
static void	move_content_remove_last_node(t_lstm *head)
{
	t_lstm	*tmp;
	t_lstm	*last_node;

	free(head->p);
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	last_node = head;
	while (last_node->next)
		last_node = last_node->next;
	if (head == last_node)
	{
		head->p = NULL;
		return ;
	}
<<<<<<< HEAD
	/*move the content from the last node to the first one*/
	head->p = last_node->p;
	tmp = head;
	/* get the node before the last one*/
=======
	head->p = last_node->p;
	tmp = head;
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	while (tmp && tmp->next != last_node)
	{
		tmp = tmp->next;
	}
<<<<<<< HEAD
	/* make it the last node by making it point to null*/
	tmp->next = NULL;
	/* free the old last node*/
=======
	tmp->next = NULL;
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	free(last_node);
}

void	free_ft_malloc(void *ptr, int is_envp)
{
<<<<<<< HEAD
    t_lstm *tmp;
	t_lstm *head;
=======
	t_lstm	*tmp;
	t_lstm	*head;
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369

	if (!is_envp)
		head = head_of_ft_malloc_struct(NULL);
	else
		head = envp_head_of_ft_malloc_struct(NULL);
<<<<<<< HEAD
	if (!ptr)
		return;
	if (head->p == ptr)
=======
	if (ptr && head->p == ptr)
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	{
		move_content_remove_last_node(head);
		return ;
	}
<<<<<<< HEAD
    while (head)
    {
        tmp = head;
        head = head->next;
=======
	while (ptr && head)
	{
		tmp = head;
		head = head->next;
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
		if (head && head->p == ptr)
		{
			tmp->next = head->next;
			free(head->p);
			free(head);
			return ;
		}
<<<<<<< HEAD
    }
=======
	}
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
}
