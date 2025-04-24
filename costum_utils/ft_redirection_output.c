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
static void ft_remove_extra_junk(char *dest, char *src)
{
	size_t	i = 0;

	if (ft_str_isspace(src))
	{
		src = ft_str_isspace(src);
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
static int apply_redirection(char *s, size_t *i, int *status)
{
	size_t	t = 0;
	char	*fd_temp = NULL;
	char	*temp = NULL;
	int		append = 0;
	int		fd = 1;
	int		fd_file = 0;
	int		chng = 0; // this is in case we have a valid fd before the '>', I save the index of the num cuz I'll have to remove it from the string;   

    chng = *i;
	fd_temp = ft_strldup((ft_strr_isspace(s, *i) + 1), &s[*i] - (ft_strr_isspace(s, *i) + 1));
	//fd_temp = ft_strldup(rdl_args[i], ft_strchr(rdl_args[i], '>') - rdl_args[i]); // parsing the part before '<' if there's any
	if (fd_temp && fd_temp[0] && fd_temp[0] != '>')
	{
	//	if (temp[1] && temp[1] == '>')
	//		temp++;
		fd = costum_atoi(fd_temp, status); // handle INT_MAX and if the fd contains a char
		if (*status != 2)
			chng = (ft_strr_isspace(s, *i) + 1) - s;
	}
	//i = s - ft_strchr(&s[i], '>');
	t = *i + 1;
	while (s[t] == ' ' || s[t] == '\t' || s[t] == '\v' || s[t] == '\f' || s[t] == '\r')
		t++;
	temp = &s[t];
	if (temp && temp[0] == '>')
	{
		append = 1;
		temp++;
	}
	// need to check if the file name is valid or not, also quotation make a difference !!
	if (!temp[0] || temp[0] == '\n')
		return(ft_putstr("minishell: syntax error near unexpected token `newline'", 2), free(fd_temp), 1);
	if (ft_str_isspace(temp))
		temp = ft_strldup(temp, ft_str_isspace(temp) - temp);
	else
		temp = ft_strdup(temp);
	if (append)
		fd_file = open(temp, O_WRONLY|O_CREAT|O_APPEND, 00644);
	else
		fd_file = open(temp, O_WRONLY|O_CREAT|O_TRUNC, 00644);
	if (fd_file < 0)
		return (perror("minishell: "), free(fd_temp), free(temp), *status = 1, 1);
	fd = dup2(fd_file, fd);
	if (fd < 0)
		return(ft_putstr("minishell: ", 2), ft_putstr(fd_temp, 2), ft_putstr(": ", 2), perror(""), close(fd_file), free(fd_temp), free(temp), *status = 1, 1);
	free(temp);
	free(fd_temp);
	ft_remove_extra_junk(&s[chng], &s[t]);
	*i = chng;
    return (0);
}
int	parse_redirection(char *s, int *status)
{
	size_t	i = 0;
	int     f_d = 0;
    int     f_s = 0;

	while (s[i])
	{        
		if (s[i] == '\'')
			f_s = !f_s;
        if (s[i] == '\"')
            f_d = !f_d;
		if (!f_d && !f_s && s[i] == '>')
		{
            if (apply_redirection(s, &i, status))
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