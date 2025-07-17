#include "../minishell.h"

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

static char *c_expand(char *str, char **envp, unsigned char *status)
{
	size_t	i = 0;
	size_t	len = 0;
	char	*ptr = NULL;
	char	*key = NULL;
	char	*var = NULL;

	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '_' || ft_isalpha(str[i + 1])))
		{
			i++;
			len = 0;
			while (str[i + len] && ft_isalnum(str[i + len]))
				len++;
			key = ft_strldup(&str[i], len);
			var = ft_getenv(key, envp, status);
			if (var)
				ptr = ft_strjoinf(ptr,var);
			//free(key);
			free_ft_malloc(key, 0);
			i += len;
		}
		else
		{
			ptr = c_strjoinf(ptr,str[i]);
			i++;
		}
	}
	free_ft_malloc(str, 0);
	//free(str);
	return(ptr);
}

/*
	checks wether the argument name; which is the name of a file, is already in the linked list of heredooc;
	meaning it will be used to save the input of another heredoc therefore we need to use another name;
*/
static int name_reserved(char *name, t_data *data)
{
	t_heredoc	*temp = data->heredooc;
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
static char *create_file_name(t_data *data)
{
    char    *og_name = ".tmp.txt";
    char    *counter = NULL;
    char    *name = NULL;
    int     count = 0; // change this to long
    name = ft_strdup(og_name);
    while ((access(name, F_OK) == 0) || ((name_reserved(name, data)) == 1)) // change this to long
    {
        //free(name);
		free_ft_malloc(name, 0);
        counter = ft_itoa(count);
        name = ft_strjoin(og_name, counter);
        //free(counter);
		free_ft_malloc(counter, 0);
        count++;
		if (count == 2147483647)
			return (unlink(name), name);
    }
    return (name);
}
int     ft_new_isheredoc(char *p, t_data *data, char *file_name)
{
    char    *tmp;
    char    *dl;
	int		fd;
	int		isquote = 0;
    int     index_ret = 0;

	(void)data;
	if (!(p[2]) && (p[2] == '<' || p[2] == '>'))
		{return(ft_putstr("minishell: syntax error near unexpected token `newline'\n", 2), -1);}
	dl = heredoc_old_delimiter(p, &isquote, &index_ret);
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
			tmp = c_expand(tmp, data->envp, &(data->status));
		//c_putstr_fd(fd, tmp);
		ft_putstr(tmp, fd);
		write(fd, "\n", 1);
		free_ft_malloc(tmp, 0);
	}
	free_ft_malloc(dl, 0);
	close(fd);
	return(index_ret);
}
void free_heredoc(t_data *data, int m_unlink)
{
    t_heredoc   *temp = data->heredooc;
    t_heredoc   *temp_f;

    if (!temp)
        return;
    while (temp && temp->next)
    {
        temp_f = temp;
        temp = temp->next;
        if (m_unlink)
        	{unlink(temp_f->file_name);}	 // check for error ?
        /*free(temp_f->file_name);
        free(temp_f);*/
		free_ft_malloc(temp_f->file_name, 0);
		free_ft_malloc(temp_f, 0);
    }
    if (m_unlink)
        {unlink(temp->file_name);}
    /*free(temp->file_name);
    free(temp);*/
	free_ft_malloc(temp->file_name, 0);
	free_ft_malloc(temp, 0);
    data->heredooc = NULL;
}
int create_file_heredoc(t_data *data)
{
    t_heredoc	*new = ft_calloc(sizeof(t_heredoc));
    t_heredoc   *temp = data->heredooc;
    new->file_name = create_file_name(data);
    int     ret = 0;

    if (!data->heredooc)
    {
        data->heredooc = new;
    }
    else
    {
        while(temp->next)
        {
            temp = temp->next;
        }
        temp->next = new;
    }
    return (ret);
}

void	wait_a_reap_exit_code(t_data *data, int child_pid)
{
	int	child_status;

	child_status = 0;
	sigaction(SIGINT, &(data->S_SIG_IGN), NULL);
    waitpid(child_pid, &child_status, 0);
	sigaction(SIGINT, &(data->SIG_INT), NULL);
    if (WIFEXITED(child_status))
    	data->status = (WEXITSTATUS(child_status));
    else if (WIFSIGNALED(child_status))
	{
        data->status = WTERMSIG(child_status) + 128;
		if (!data->is_a_pipe && data->status == 130)
		{
			write(1, "\n", 1);
		}
	}
    free_heredoc(data, 1); // files get deleted and the struct gets freed.
    data->heredooc = NULL;
	free_ft_malloc(data->p_rdl, 0);
	data->p_rdl = NULL;
}


static void	init_heredoc_prompt_file(t_data *data)
{
	size_t	i;
	int		f_d;
    int		f_s;
	t_heredoc *temp;

	i = 0;
	f_d = 0;
    f_s = 0;
	temp = data->heredooc;
    while (data->p_rdl[i])
    {
        if (data->p_rdl[i] == '\'' && !f_d)
            f_s = !f_s;
        if (data->p_rdl[i] == '\"' && !f_s)
            f_d = !f_d;
    	if (!f_d && !f_s && data->p_rdl[i] == '<' && data->p_rdl[i + 1] == '<')
        {
            while (temp && temp->taken)
                temp = temp->next;
            temp->taken = 1;
            i += ft_new_isheredoc((&data->p_rdl[i]), data, temp->file_name);
        }
        else
        	i++;
    }
}
/* the below functions checks if the cmd includes a heredoc op, 
	if It does it allocates a node for it and a name for the file  */
static int	init_heredoc_struct(t_data *data)
{
	size_t	i = 0;
	int		found = 0;
	char	q = 0 ;

	while (data->p_rdl[i])
	{
		if (found > HEREDOC_MAX)
		{
			ft_putstr("minishell: maximum here-document count exceeded\n", 2);
			config_malloc(NULL, 2, 2);
			exit(2);
		}
		if ((data->p_rdl[i] == '\'' || data->p_rdl[i] == '\"') && !q)
			q = data->p_rdl[i];
		else if (q && data->p_rdl[i] == q)
			q = 0;
		if (!q && data->p_rdl[i] == '<' && data->p_rdl[i + 1] == '<')
		{
            create_file_heredoc(data);
            i += 2;
            found++;
		}
		else
			i++;
	}
	return (found);
}

int here_doc(t_data *data)
{
    int     child_pid;

    if (init_heredoc_struct(data))
    {
        child_pid = fork();
        if (child_pid < 0)
            return (perror(""), errno); // config_malloc ?
        if (child_pid == 0)
        {
            data->is_a_pipe = 1;
			sigaction(SIGINT, &(data->S_SIG_DFL), NULL);
			init_heredoc_prompt_file(data);
        }
        else
			wait_a_reap_exit_code(data, child_pid);
    }
	return (0);
}

/*int     ft_isheredoc(char *p, char **envp, unsigned char *status, t_data *data)
{
    char    *tmp;
    char    *dl;
	int		fd;
	int		isquote = 0;
//	int 	temp_fd_1 = -1;

	(void)data;
	if (!(p[2]) && (p[2] == '<' || p[2] == '>'))
		{return(ft_putstr("minishell: syntax error near unexpected token `newline'\n", 2), -1);}
		dl = heredoc_delimiter(p,&isquote);
		if (!dl)
			return(-1); // failed malloc protection
		// I might need to save STDIN, STDOUT before I execute readline, and later restart them.
		fd = open("/tmp/tmp.txt", O_RDWR | O_CREAT | O_TRUNC , 0777); // change perms
		if (fd < 0)
			return (perror(""), 0);
		if (!isatty(0))
		{
			dup2(data->fd0, 0);
		}
		if (!isatty(1))
		{
			temp_fd_1 = dup(1);
			dup2(data->fd1, 1);
		}
		while (1)
		{
			tmp = readline("> ");
			if (!tmp || ft_strcmp(tmp, dl))
			{
				free(tmp);
				break;
			}
			if (!isquote && tmp[0])
				tmp = c_expand(tmp, envp, status);
			c_putstr_fd(fd, tmp);
			free(tmp);
		}
		free(dl);
		close(fd);
		fd = open("/tmp/tmp.txt", O_RDWR, 0777);
		if (fd < 0)
			return (perror(""), errno);
		if (dup2(fd, 0) < 0)
			{return (close(fd), perror(""), errno);}
		if (temp_fd_1 != -1 && dup2(temp_fd_1, 1) < 0)
		{
			return (close(temp_fd_1), perror(""), errno);
		}
		close(fd);
		// unlink
		return(0);
}*/