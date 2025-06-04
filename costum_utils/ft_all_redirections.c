#include "../minishell.h"

/*static void	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (size == 0)
		return ;
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
static void remove_spaces_in_beg(char *s)
{
	size_t i = 0;

	while (s[i] && (s[i] == ' ' || s[i] == '\t')) // whitespaces maybe ?
		i++;
	if (i)
		ft_strlcpy(&s[0], &s[i], ft_strlen(s));
	i = ft_strlen(s) - 1;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i--;
	if (i != (ft_strlen(s) - 1))
		s[i + 1] = 0;
}*/	
static char	*ft_strr_isspace(char *s, size_t n) // this is like strchr, but looks for the first occuence of isspace'in s starting from s[n] and going backwards;
{
	if (!n || !s)
		return (NULL);
	while(s[n] && n > 0)
	{
		if (s[n] == ' ' || (s[n] >= 9 && s[n] <= 13))
			return (s + n);
		n--;
	}
	return (NULL);
}
static char	*ft_str_isspace(char *s)
{
	size_t	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
			return (s + i);
		i++;
	}
	return (NULL);
}
static void move_remaining(char *s, int src, int dst)
{
	while (s[src])
	{
		s[dst] = s[src];
		src++;
		dst++;
	}
	s[dst] = 0;
}
static  char    *c_strpbrk(char *s)
{
    size_t  i;

    i =  0;
    while(s[i])
    {
        if (!ft_isalnum(s[i]) && s[i] != '_') 
            return (&s[i]);
        i++;
    }
    return (&s[i]);
}
static void ft_remove_extra_junk(char *dest, char *src, size_t n)
{
	size_t		i = 0;
	char		*temp = src;
	//while (*src == ' ' || *src == '\t' || *src == '\v' || *src == '\f' || *src == '\r')
	//	src++;
	if (ft_str_isspace(src) || ft_strchr(src, '<') || ft_strchr(src, '>'))
	{
		temp = ft_str_isspace(src);
		if (!temp)
		{
			temp = ft_strchr(src, '<');
			if (temp && temp < ft_strchr(src, '>'))
				src = temp;
			else
				src = ft_strchr(src, '>');
		}
		else
			src = temp;
		if (!n)
			src++; // I've done this in case the redirection is the first thing in the command this way the space after the redi won't get copied;
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	else
		dest[0] = 0;

}
static char *parsing_input_fd(char *s, size_t i, int *fd, int *dest)
{
	char			*fd_input;
	unsigned char	status;

	fd_input = NULL;
	status = 0;
	if (ft_strr_isspace(s, i))
		fd_input = ft_strldup((ft_strr_isspace(s, i) + 1), &s[i] - (ft_strr_isspace(s, i) + 1));
	else if (i > 0)
		fd_input = ft_strldup(s, i);
	else
		fd_input = NULL;
	if (fd_input && fd_input[0] && fd_input[0] != '>' && fd_input[0] != '<')
	{
		*fd = costum_atoi(fd_input, &status, *fd); // handle INT_MAX and if the fd contains a char
		if (status != 2)
			*dest = 0; // this is in case the redi is the first thing in the command but we have a valid fd and we want to remove it;
		if (ft_strr_isspace(s, i) && status != 2)
			*dest = ((ft_strr_isspace(s, i) + 1) - s);
	}
	return (fd_input);
}

static char *var_expansion(char **str, char **envp, int *n, char **full_str, unsigned char *status)
{
	char    *extract = NULL;
    char    *var = NULL;
    char    *left_side = NULL;
    char    *right_side = NULL;
	char *s = *str;
	int  ret = (*str) - (*full_str); // this is to save the index where the '$' was found and return it;
	int i = (*str) - (*full_str) + (*n); // the size of how much left side shoud be
	extract = ft_strldup(&s[*n + 1], c_strpbrk(&s[*n + 1]) - &s[*n + 1]);
	var = ft_getenv(extract, envp, status);
	left_side = ft_strldup(*full_str, (i));
	if (!var && !(*n))
		return (ft_putstr("minishell: $" , 2), ft_putstr(extract, 2), ft_putstr(": ambiguous redirect\n", 2), free(left_side), free(extract), NULL);
	if (var)
		left_side =	ft_strjoinf(left_side, var);
	right_side = ft_strdup(c_strpbrk(&s[*n + 1]));
	free(*full_str);
	s = ft_strjoinf(left_side, right_side);
	*full_str = s;

	if (ft_strlen(var))
		*n += (ft_strlen(var)); // used to be (ft_strlen(var) - 1) can't remember why I added the -1
	//else
	//	*n -= ft_strlen(extract);
	free(right_side);
	free(extract);
	return (&s[ret]);
	//return (&s[i]);
}

static int expand_rm_quotes(char *str, char **envp, char **full_str, unsigned char *status)
{
	int i = 0;
	int j = 0;
	int q = 0;
	int     f_d = 0;
    int     f_s = 0;
	// need to expand env var here
	while (str[i] && ((!q && str[i] != ' ') || q) && ((ft_strchr("<>", str[i]) && q) || !(ft_strchr("<>", str[i])))) // need to replace the space with (issapce);
	{
		if (str[i] == '\'' && !f_d)
			f_s = !f_s;
		if (str[i] == '\"' && !f_s)
			f_d = !f_d;

		if (str[i] == '$' && !f_s && (ft_isalpha(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			move_remaining(str, i, j);
			// replace the variable with it's value if it exist otherwise replace it with nothing
			i = j; // update the index in case we deleted quotes;
			str = var_expansion(&str, envp, &i, full_str, status);
			if (!str)
				return (-1);
			// handle if expnaded variable doesn't exist
			j = i; // I do this so that the program skips the expanded var, so that if the var has quotes or spaces it won't get deleted or stopped;
		}
		if (!q && (str[i] == '\'' || str[i] == '\"')) //    "test file" / i = 11
			q = str[i];                                    // test file
		else if(str[i] != q && ((!q && str[i] != ' ') || q) && ((ft_strchr("<>", str[i]) && q) || !(ft_strchr("<>", str[i])))) // whilespaces instead of space
		{
			str[j] = str[i];
			j++;
		}
		else
			q = 0;
		if (((str[i] && str[i] != ' ') || (str[i] && q)) && ((ft_strchr("<>", str[i]) && q) || !(ft_strchr("<>", str[i]))))
			i++;
	}
	if (j < i)
		move_remaining(str, i, j);
	return (j);
}

static int open_assign_fd(char *s, int *fd, int mode, int append, int *ret)
{
	int		fd_file = 0;
	char	*temp;
	//fd = open("/proc/sys/kernel/pid_max", (argc > 1) ? O_RDWR : O_RDONLY);
	if (append)
		fd_file = open(s, O_WRONLY|O_CREAT|O_APPEND, 00644);
	else if (mode && !append)
		fd_file = open(s, O_WRONLY|O_CREAT|O_TRUNC, 00644);
	else if (!mode)
		fd_file = open(s, O_RDONLY, 00644);
	if (fd_file < 0)
		return(temp = ft_strjoin("minishell: ", s), temp = ft_strjoinf(temp, ": "), temp = ft_strjoinf(temp, strerror(errno)) , temp = ft_strjoinf(temp, "\n"), ft_putstr(temp, 2), free(temp), *ret = 1 , 1);
	//	return (ft_putstr("minishell: ", 2), ft_putstr(s, 2), ft_putstr(": ", 2), perror(""), fflush(stderr), *ret = 1 , 1);
	*fd = dup2(fd_file, *fd);
	close(fd_file);
	if (*fd < 0)
		return(*ret = 2, 2);
 	return (0);
}

static int	open_file_redi(char *s, int *fd, int mode, int *end, char **envp, char **full_str, unsigned char *status)
{
	int		append = 0;
	int		begin = 0;
	int		ret = 0;
	int		old_i = s - (*full_str);
	
	if (s && s[begin] == '>')
	{
		append = 1;
		begin += 1;
	}
	while (s[begin] == ' ' || s[begin] == '\t' || s[begin] == '\v' || s[begin] == '\f' || s[begin] == '\r')
		begin += 1;
	*end = expand_rm_quotes(&s[begin], envp, full_str, status);
	if (*end == -1)
		return (1);
	s = (*full_str) + old_i;
	if (*end)
		s = ft_strldup(&s[begin], *end); // change this so that variable expansion gets applied here
	else
		s = ft_strdup(&s[begin]);
	*end += begin;
	if (open_assign_fd(s, fd, mode, append, &ret))
		return (free(s), ret);
	free(s);
	return (0);
}

static int apply_redirection(size_t *i, unsigned char *status, int fd, char **envp, char **full_str)
{
	char	*fd_input; // this is used to store between a 'isspace' and '>' if there are any, after that we check if It's a valid 'fd';
	int		dest; // this is in case we have a valid fd before the '>', I save the index of the num cuz I'll have to remove it from the string;   
	int		f_mode; // free mode
	int		end_file_name = 0;
	char	*temp; // this is done cuz perror might be buffering the strings;

    dest = *i;
	fd_input = parsing_input_fd((*full_str), *i, &fd, &dest);//, status);
	if ((*full_str)[*i] == '>')
		f_mode = open_file_redi(&(*full_str)[*i + 1], &fd, 1, &end_file_name, envp, full_str, status);
	else
		f_mode = open_file_redi(&(*full_str)[*i + 1], &fd, 0, &end_file_name, envp, full_str, status);
	if (f_mode == 1)
		return (free(fd_input), *status = 1, 1);
	if (f_mode == 2)
		return(temp = ft_strjoin("minishell: ", fd_input), temp = ft_strjoinf(temp, strerror(errno)) , ft_putstr(temp, 2), free(fd_input), free(temp), *status = 1, 2);
	free(fd_input);
	if (end_file_name) // this indicates wether the file name is the last thing in the string or not
		*i += end_file_name;
	else
		*i += 1;
	ft_remove_extra_junk(&(*full_str)[dest], &(*full_str)[*i], *i);
	*i = dest;
    return (0);
}

static void remove_heredoc(char *s)
{
	size_t i = 0;
    size_t st = 0;
    size_t f = 0;
    size_t j = 0;
    char    q = 0;

    i = 2;
    f = 0;
    while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
        i++;
    st = i;
    while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
    {
        if (!q && (s[i] == '\'' || s[i] == '\"'))
        {
            q = s[i++];
   //         *isquote = 1;
        }
        while(q && s[i] != q)
            i++;
        q = 0;
        i++;
    }
	while (s[i]) // ft_strcpy
    {
        s[f + j] = s[i];
        j++;
        i++;
    }
    s[f + j] = 0;
}
int found_here_doc(t_data *data, char *s)
{
	t_heredoc	*temp = data->heredooc;
	int			fd;
	while(temp->next && temp->arg_num)
	{
		temp = temp->next;
	}

	fd = open(temp->file_name, O_RDONLY);
	if (fd < 0)
		return (perror(""), errno);
	if (dup2(fd, 0) < 0)
		{return (close(fd), perror(""), errno);}
	close(fd);
	temp->arg_num = 1;
	remove_heredoc(s);
	return (0);
}

int	parse_redirection(char **full_str, unsigned char *status, char **envp, t_data *data)
{
	size_t	i = 0;
	int     f_d = 0;
    int     f_s = 0;

	while ((*full_str)[i])
	{        
		if ((*full_str)[i] == '\'' && !f_d)
			f_s = !f_s;
        if ((*full_str)[i] == '\"' && !f_s)
            f_d = !f_d;
		if (!f_d && !f_s && (*full_str)[i] == '>')
		{
			if (apply_redirection(&i, status, 1, envp, full_str))
				return (1);
		}
		else if (!f_d && !f_s && (*full_str)[i] == '<' && (*full_str)[i + 1] == '<')
		{
			if ((found_here_doc(data, (*full_str) + i)))
                return (1);
		}
		else if (!f_d && !f_s && (*full_str)[i] == '<')
		{
			if (apply_redirection(&i, status, 0, envp, full_str))
                return (1);
		}
		else
			i++;
	}
	//remove_spaces_in_beg(*full_str); // not needed anymore cuz the split takes care of the spaces
	return (0);
}

// old function where I used to execute redirection after splitting the command;
/*int parse_redirection(char **rdl_args, int *status)
{
	size_t	i = 0;
	char	*fd_temp;
	char	*temp;
	int		append = 0;
	int		fd = 1;
	int		fd_file = 0;

	while (rdl_args[i])
	{
		if (ft_strchr(rdl_args[i], '>'))
		{
			fd_temp = ft_strldup(rdl_args[i], ft_strchr(rdl_args[i], '>') - rdl_args[i]); // parsing the part before '<' if there's any
			if (fd_temp && fd_temp[0])
				fd = costum_atoi(fd_temp, status);
			temp = ft_strchr(rdl_args[i], '>') + 1;
			if (temp && temp[0] == '>')
			{
				append = 1;
				temp++;
			}
		//	if (fd > 1023 || *status == 1) // if the passed 'fd' in the argument is greater than 1023 we need to stop the executing and return an error
		//		return (ft_putstr("minishell: ", 2), ft_putstr(temp, 2), ft_putstr(": Bad file descriptor\n", 2), free(temp), *status = 1, 1); // maybe not needed ?
		//	if (*status == 2) // this is in case the argument is greater than INT_MAX or It doesn't contain an int	
		//		rdl_args[i] = fd_temp; // we need to passe the chars before '>' as an argument, placed before the current one.
		//	else
		//	{
				if (!temp[0])
				{
					free_move(rdl_args, i);
					temp = rdl_args[i];
					if (!temp)
						return(ft_putstr("minishell: syntax error near unexpected token `newline'", 2), free(fd_temp), 1);
				}
				if (append)
					fd_file = open(temp, O_RDWR|O_CREAT|O_APPEND, 00644);
				else
					fd_file = open(temp, O_RDWR|O_CREAT|O_TRUNC, 00644);
				if (fd_file < 0)
					return (perror("minishell: "), free(fd_temp), *status = 1, 1);
				fd = dup2(fd_file, fd);
				if (fd < 0)
					return(ft_putstr("minishell: ", 2), ft_putstr(fd_temp, 2), ft_putstr(": ", 2), perror(""), close(fd_file), free(fd_temp), *status = 1, 1);
				free_move(rdl_args, i);
				if (*status != 2)
					free(fd_temp);
				else
					rdl_args[i] = fd_temp;
		//	}
			i = 0;
		}
		i++;
	}
	if (*rdl_args == NULL)
		return (1);
	return (0);
}*/