/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:00:09 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/26 18:57:03 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* creates a file and gives the user a prompt, the input of the user
   is saved on the file*/
static int	execute_heredoc(char *p, t_data *data, char *file_name)
{
	char	*dl;
	int		isquote;
	int		index_ret;

	isquote = 0;
	index_ret = 0;
	dl = heredoc_delimiter(p, &isquote, &index_ret);
	create_file_give_prompt(data, dl, isquote, file_name);
	free_ft_malloc(dl, 0);
	return (index_ret);
}

/* creates a file and gives the user a prompt, the input of the user
   is saved on the file*/
static void	init_heredoc_prompt_file(t_data *data)
{
	size_t		i;
	char		q;
	t_heredoc	*temp;

	i = 0;
	q = 0;
	temp = data->heredooc;
	while (data->p_rdl[i])
	{
		if (!q && (data->p_rdl[i] == '\'' || data->p_rdl[i] == '\"'))
			q = data->p_rdl[i];
		else if (q && data->p_rdl[i] == q)
			q = 0;
		if (!q && data->p_rdl[i] == '<' && data->p_rdl[i + 1] == '<')
		{
			i += execute_heredoc((&data->p_rdl[i]), data, temp->file_name);
			temp = temp->next;
		}
		else
			i++;
	}
}

/* the parent (minishell) here waits for the child (heredoc) to finish it's job
	reaps or collects the exit status of the child then frees t_heredoc
	(linked list used by heredoc) and unlinks the created files by
	the child (heredoc)*/
static void	wait_a_reap_exit_code(t_data *data, int child_pid)
{
	int	child_status;

	child_status = 0;
	sigaction(SIGINT, &(data->s_sig_ign), NULL);
	waitpid(child_pid, &child_status, 0);
	sigaction(SIGINT, &(data->sig_int), NULL);
	if (WIFEXITED(child_status))
		data->status = (WEXITSTATUS(child_status));
	else if (WIFSIGNALED(child_status))
	{
		data->status = WTERMSIG(child_status) + 128;
		if (data->status == 130)
		{
			write(1, "\n", 1);
		}
	}
	free_heredoc(data);
	data->heredooc = NULL;
	free_ft_malloc(data->p_rdl, 0);
	data->p_rdl = NULL;
}

void	here_doc(t_data *data)
{
	int	child_pid;

	if (check_for_heredoc_create_node(data, 0, 0))
	{
		child_pid = fork();
		if (child_pid < 0)
			print_free_exit(FORK_FAILED, errno);
		if (child_pid == 0)
		{
			close_dup_fds();
			data->is_a_child = 1;
			data->status = 0;
			sigaction(SIGINT, &(data->s_sig_dfl), NULL);
			init_heredoc_prompt_file(data);
		}
		else
			wait_a_reap_exit_code(data, child_pid);
	}
	return ;
}
