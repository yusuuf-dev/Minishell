#include "../minishell.h"

/* the below function checks if the cmd includes a heredoc op, 
	if It does it allocates a node for it and a name for the file  */
int	check_for_heredoc_create_node(t_data *data, size_t i, int found)
{
	char	q;

	q = 0;
	while (data->p_rdl[i])
	{
		if (found > HEREDOC_MAX)
		{
			ft_putstr("minishell: maximum here-document count exceeded\n", 2);
			config_malloc(NULL, 0, 2);
			exit(2);
		}
		if (!q && (data->p_rdl[i] == '\'' || data->p_rdl[i] == '\"'))
			q = data->p_rdl[i];
		else if (q && data->p_rdl[i] == q)
			q = 0;
		if (!q && data->p_rdl[i] == '<' && data->p_rdl[i + 1] == '<')
		{
            create_t_heredoc_node(data);
            i += 2;
            found++;
		}
		else
			i++;
	}
	return (found);
}
static char *c_strjoinf(char *s1, char c)
{
	size_t i;
	size_t len;
	char	*ptr;

	len = ft_strlen(s1);
	ptr = ft_malloc((len + 2) * sizeof(char));
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = c;
	ptr[i] = 0;
	return (ptr);
}
static char *c_expand(char *str, t_data *data, size_t i, size_t	len)
{
	char	*ptr;
	char	*key;
	char	*var;

	ptr = NULL;
	while (str && str[i])
	{
		if (str[i] == '$' && validchar_helper(str[i + 1]))
		{
			len = getlen_helper(str,i + 1);
			key = ft_strldup(&str[i + 1], len);
			if (ft_strcmp(key, "?"))
				var = ft_getenv("?", data->envp, &data->status);
			else
				var = ft_getenv(key, data->envp, &data->status);
			if (var)
				ptr = ft_strjoinf(ptr,var);
			i += len;
		}
		else
			ptr = c_strjoinf(ptr,str[i]);
		i++;
	}
	free_ft_malloc(str, 0);
	return(ptr);
}
/* this is were the file is created and the prompt is given */
void	create_file_give_prompt(t_data *data, char *dl, int isquote, char *file_name)
{
	int		fd;
	char	*tmp;

	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC , 0600); // change perms
	if (fd < 0)
	{
		perror("");
		config_malloc(NULL, 2, 2);
		exit(errno);
	}
	while (1)
	{
		tmp = ft_read_line_gnl(0);
		if (!tmp || ft_strcmp(tmp, dl))
		{
			free_ft_malloc(tmp, 0);
			break;
		}
		if (!isquote && tmp[0])
			tmp = c_expand(tmp,data,0,0);
		ft_putstr(tmp, fd);
		write(fd, "\n", 1);
		free_ft_malloc(tmp, 0);
	}
	close(fd);
}