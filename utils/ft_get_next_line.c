#include "../minishell.h"
// static void	free_null(char **p)
// {
// 	if (p && *p)
// 	{
// 		// free(*p);
// 		// *p = NULL;
// 	}
// }

static char	*empty_or_error(char *old_stash, char **stash)
{
	if (old_stash && ((ft_strchr(old_stash, '\n'))))
		return (*stash = ft_strdup(ft_strchr(old_stash, '\n') + 1), (ft_substr_c(
					old_stash, 0, ft_strchr(old_stash, '\n') - old_stash + 1)));
	else
	{
		if (old_stash)
		{
			//free_null(stash);
			return (old_stash);
		}
		else
		{
			//free_null(stash);
			return (NULL);
		}
	}
}

static char	*return_line_update_stash(char *o_stash, char **stash)
{
	if (!o_stash)
		o_stash = *stash;
	// else
	// 	free_null(stash);
	*stash = ft_strdup(ft_strchr(o_stash, '\n') + 1);
	if (!(*stash))
		*stash = NULL;
	return (ft_substr_c(o_stash, 0, ((ft_strchr(o_stash, '\n')) - o_stash + 1)));
}

char	*get_next_line(int fd)
{
	static char	*stash;
	//char *stash = NULL;
	ssize_t		rd;
	char		*o_stash;

	o_stash = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash)
	{
		o_stash = ft_strdup(stash);
		// free_null(&stash);
	}
	stash = ft_calloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!stash)
		return (NULL);
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