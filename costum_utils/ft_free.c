#include "../minishell.h"
/*void	move_all_the_nodes(t_lstm *move)
{
	t_lstm	*tmp;
	t_lstm	*last_node = move;


	while (last_node)
	{
		last_node = last_node->next;
	}

}*/
t_lstm	*envp_head_of_ft_malloc_struct(t_lstm *head)
{
	static t_lstm *ptr = NULL;

	if (head)
		ptr = head;
	return (ptr);
}

t_lstm	*head_of_ft_malloc_struct(t_lstm *head)
{
	static t_lstm *ptr = NULL;

	if (head)
		ptr = head;
	return (ptr);
}

static void move_content_remove_last_node(t_lstm *head)
{
	t_lstm *tmp;
	t_lstm *last_node;

	free(head->p);
	/* get the last node*/
	last_node = head;
	while (last_node->next)
		last_node = last_node->next;
	/*move the content from the last node to the first one*/
	head->p = last_node->p;
	tmp = head;
	/* get the node before the last one*/
	while (tmp->next != last_node)
	{
		tmp = tmp->next;
	}
	/* make it the last node by making it point to null*/
	tmp->next = NULL;
	/* free the old last node*/
	free(last_node);
}

void	free_ft_malloc(void *ptr, int is_envp)
{
    t_lstm *tmp;
	t_lstm *head;

	if (!is_envp)
		head = head_of_ft_malloc_struct(NULL);
	else
		head = envp_head_of_ft_malloc_struct(NULL);
	if (!ptr)
		return;
	if (head->p == ptr)
	{
		move_content_remove_last_node(head);
	}
    while (head)
    {
        tmp = head;
        head = head->next;
		if (head->p == ptr)
		{
			tmp->next = head->next;
			free(head->p);
			free(head);
			return ;
		}
    }
}
