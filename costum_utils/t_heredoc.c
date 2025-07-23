/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:41:26 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/23 12:02:34 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/* frees the t_heredoc linked list and unlinks the files that were
    used.*/
void	free_heredoc(t_data *data)
{
	t_heredoc	*temp;
	t_heredoc	*temp_f;

	temp = data->heredooc;
	if (!temp)
		return ;
	while (temp && temp->next)
	{
		temp_f = temp;
		temp = temp->next;
		unlink(temp_f->file_name);
		free_ft_malloc(temp_f->file_name, 0);
		free_ft_malloc(temp_f, 0);
	}
	unlink(temp->file_name);
	free_ft_malloc(temp->file_name, 0);
	free_ft_malloc(temp, 0);
	data->heredooc = NULL;
}

/* checks if the name is already used by another node in the linked list*/
static int	if_name_reserved(char *name, t_data *data)
{
	t_heredoc	*temp;

	temp = data->heredooc;
	if (!temp)
		return (0);
	while (temp && temp->next)
	{
		if (ft_strcmp(temp->file_name, name))
			return (1);
		temp = temp->next;
	}
	if (ft_strcmp(temp->file_name, name))
		return (1);
	return (0);
}

static char	*generate_file_name(t_data *data)
{
	char	*og_name;
	char	*counter;
	char	*name;
	int		count;

	og_name = ".tmp.txt";
	counter = NULL;
	name = NULL;
	count = 0;
	name = ft_strdup(og_name);
	while ((access(name, F_OK) == 0) || ((if_name_reserved(name, data)) == 1))
	{
		free_ft_malloc(name, 0);
		counter = ft_itoa(count);
		name = ft_strjoin(og_name, counter);
		free_ft_malloc(counter, 0);
		count++;
		if (count == 2147483647)
			return (name);
	}
	return (name);
}

/* creates a node for the linked list used by the heredoc and generates a
    file nameto be created later by the heredoc_execute*/
void	create_t_heredoc_node(t_data *data)
{
	t_heredoc	*new;
	t_heredoc	*temp;

	new = ft_calloc(sizeof(t_heredoc));
	temp = data->heredooc;
	new->file_name = generate_file_name(data);
	if (!data->heredooc)
	{
		data->heredooc = new;
	}
	else
	{
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	return ;
}

/* this here is used if there's a pipe and heredoc ops in the cmd, 
	this works as follows: */
/*    - the minishell creates the linked list and gives the user the prompt,
		saves the input into a file */
/*    - after, when we split the cmd so that each one gets executed by itself*/
/* (how pipes are supposed to work) we need to assign each cmd in the pipeline*/
/*        It's correct node in the linked list (which contains a file name)*/
/*        and I achieve this by the int 'taken' and this functions sets 
	that int to 1 only if the cmd contains a heredoc operator */
int	update_used_heredoc_list(char *s, t_data *data, int found, int i)
{
	t_heredoc	*temp;
	char		q;

	q = 0;
	temp = data->heredooc;
	i = 0;
	found = 0;
	while ((s)[i] && !found)
	{
		if (!q && (s[i] == '\'' || s[i] == '\"'))
			q = s[i];
		else if (q && s[i] == q)
			q = 0;
		if (!q && s[i] == '<' && s[i + 1] == '<')
			found = 1;
		i++;
	}
	if (!temp || !found)
		return (1);
	while (temp->next && temp->taken)
	{
		temp = temp->next;
	}
	temp->taken = 1;
	return (1);
}
