<<<<<<< HEAD
#include "../minishell.h"
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:44 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/19 10:36:52 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
static void	free_null(char **p)
{
	if (p && *p)
	{
		free_ft_malloc(*p, 0);
		*p = NULL;
	}
}

static char	*empty_or_error(char *old_stash, char **stash)
{
	if (old_stash && ((ft_strchr(old_stash, '\n'))))
<<<<<<< HEAD
		return (*stash = ft_strdup(ft_strchr(old_stash, '\n') + 1), (ft_substr_c(
					old_stash, 0, ft_strchr(old_stash, '\n') - old_stash + 1)));
=======
		return (*stash = ft_strdup(ft_strchr(old_stash, '\n') + 1),
			(ft_substr_c(old_stash, 0, ft_strchr(old_stash, '\n') - old_stash
					+ 1)));
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	else
	{
		if (old_stash)
		{
			free_null(stash);
			return (old_stash);
		}
		else
		{
			free_null(stash);
			return (NULL);
		}
	}
}

static char	*return_line_update_stash(char *o_stash, char **stash)
{
	if (!o_stash)
		o_stash = *stash;
	else
		free_null(stash);
	*stash = ft_strdup_env(ft_strchr(o_stash, '\n') + 1);
	if (!(*stash))
		*stash = NULL;
<<<<<<< HEAD
	return (ft_substr_c(o_stash, 0, ((ft_strchr(o_stash, '\n')) - o_stash + 1)));
=======
	return (ft_substr_c(o_stash, 0, ((ft_strchr(o_stash, '\n')) - o_stash
				+ 1)));
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
<<<<<<< HEAD
	//char *stash = NULL;
=======
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	ssize_t		rd;
	char		*o_stash;

	o_stash = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash && stash[0])
	{
		o_stash = ft_strdup(stash);
		free_null(&stash);
	}
	stash = ft_calloc(sizeof(char) * (BUFFER_SIZE + 1));
	while ((!ft_strchr(o_stash, '\n')))
	{
		rd = read(fd, stash, BUFFER_SIZE);
		if (rd <= 0)
			return (empty_or_error(o_stash, &stash));
		stash[rd] = '\0';
		o_stash = ft_strjoin(o_stash, stash);
	}
	return (return_line_update_stash(o_stash, &stash));
}
