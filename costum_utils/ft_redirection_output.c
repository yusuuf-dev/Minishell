#include "../minishell.h"

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
static void ft_remove_extra_junk(char *dest, char *src, size_t n)
{
	size_t	i = 0;

	//while (*src == ' ' || *src == '\t' || *src == '\v' || *src == '\f' || *src == '\r')
	//	src++;
	if (ft_str_isspace(src))
	{
		src = ft_str_isspace(src);
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
static void move_remaining(char *s, int i, int j)
{
	while (s[i])
	{
		s[j] = s[i];
		i++;
		j++;
	}
	s[j] = 0;
}
static int rm_quotes(char *str)
{
	int i = 0;
	int j = 0;
	int q = 0;

	while (str[i] && ((!q && str[i] != ' ') || q)) // need to replace the space with (issapce);
	{
		if (!q && (str[i] == '\'' || str[i] == '\"')) //    "test file" / i = 11
			q = str[i];                                    // test file
		else if(str[i] != q)
		{
			str[j] = str[i];
			j++;
		}
		else
			q = 0;
		i++;
	}
	move_remaining(str, i, j);
	return (j);
}

static int open_assign_fd(char *s, int *fd, int mode, int append, int *ret)
{
	int		fd_file = 0;

	if (append)
		fd_file = open(s, O_WRONLY|O_CREAT|O_APPEND, 00644);
	else if (mode && !append)
		fd_file = open(s, O_WRONLY|O_CREAT|O_TRUNC, 00644);
	else if (!mode)
		fd_file = open(s, O_RDONLY, 00644);
	if (fd_file < 0)
		return (ft_putstr("minishell: ", 2), ft_putstr(s, 2), ft_putstr(": ", 2), perror(""), *ret = 1 , 1);
	*fd = dup2(fd_file, *fd);
	if (*fd < 0)
		return(close(fd_file), *ret = 2, 2);
 	return (0);
}

static int	open_file_redi(char *s, int *fd, int mode, int *end)
{
	int		append = 0;
	int		begin = 0;
	int		ret = 0;

	if (s && s[begin] == '>')
	{
		append = 1;
		begin += 1;
	}
	while (s[begin] == ' ' || s[begin] == '\t' || s[begin] == '\v' || s[begin] == '\f' || s[begin] == '\r')
		begin += 1;
	// need to check if the file name is valid or not, also quotation make a difference !!
	if (!(s[begin]) || s[begin] == '\n')
		return(ft_putstr("minishell: syntax error near unexpected token `newline'", 2), 1);
	*end = rm_quotes(&s[begin]);
	if (*end)
		s = ft_strldup(&s[begin], *end);
	else
		s = ft_strdup(&s[begin]);
	*end += begin;
	if (open_assign_fd(s, fd, mode, append, &ret))
		return (free(s), ret);
	free(s);
	return (0);
}
static char *parsing_input_fd(char *s, size_t *i, int *fd, int *dest, int *status)
{
	char	*fd_input = NULL;

	if (ft_strr_isspace(s, *i))
		fd_input = ft_strldup((ft_strr_isspace(s, *i) + 1), &s[*i] - (ft_strr_isspace(s, *i) + 1));
	else if (*i > 0)
		fd_input = ft_strldup(s, *i);
	else
		fd_input = NULL;
	if (fd_input && fd_input[0] && fd_input[0] != '>' && fd_input[0] != '<')
	{
		*fd = costum_atoi(fd_input, status, *fd); // handle INT_MAX and if the fd contains a char
		if (*status != 2)
			*dest = 0; // this is in case the redi is the first thing in the command but we have a valid fd and we want to remove it;
		if (ft_strr_isspace(s, *i) && *status != 2)
			*dest = ((ft_strr_isspace(s, *i) + 1) - s);
	}
	return (fd_input);
}
static int apply_redirection(char *s, size_t *i, int *status, int fd)
{
	char	*fd_input; // this is used to store between a 'isspace' and '>' if there are any, after that we check if It's a valid 'fd';
	int		dest; // this is in case we have a valid fd before the '>', I save the index of the num cuz I'll have to remove it from the string;   
	int		f_mode; // free mode
	int		end_file_name= 0;

    dest = *i;
	fd_input = parsing_input_fd(s, i, &fd, &dest, status);
	if (s[*i] == '>') 	
		f_mode = open_file_redi(&s[*i + 1], &fd, 1, &end_file_name);
	else
		f_mode = open_file_redi(&s[*i + 1], &fd, 0, &end_file_name);
	if	(f_mode == 1)
		return (free(fd_input), *status = 1, 1);
	else if (f_mode == 2)
		return(ft_putstr("minishell: ", 2), ft_putstr(fd_input, 2), ft_putstr(": ", 2), perror(""), free(fd_input), *status = 1, 2);
	free(fd_input);
	if (end_file_name) // this indicates wether the file name is the last thing in the string or not
		*i += end_file_name;
	else
		*i += 1;
	ft_remove_extra_junk(&s[dest], &s[*i], *i);
	*i = dest;
    return (0);
}
int	parse_redirection(char *s, int *status)
{
	size_t	i = 0;
	int     f_d = 0;
    int     f_s = 0;

	while (s[i])
	{        
		if (s[i] == '\'' && !f_d)
			f_s = !f_s;
        if (s[i] == '\"' && !f_s)
            f_d = !f_d;
		if (!f_d && !f_s && s[i] == '>' && (apply_redirection(s, &i, status, 1)))
			return (1);
		else if (!f_d && !f_s && s[i] == '<')
		{
            if (apply_redirection(s, &i, status, 0))
                return (1);
		}
		else
			i++;
	}
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