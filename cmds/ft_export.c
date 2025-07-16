#include "../minishell.h"

static  int    valid_var(char *s)
{
	size_t	i;

	i = 1;
	if (s[0] && (s[0] != '_' && !ft_isalpha(s[0])))
		return (1);
	while (s[i] && s[i] != '=') // I make the function stop if it finds the '=' cuz bash doesn't mind what the value of the varialbe is
	{							//	wether it contains (some chars other than alphanum, '_', '=').
    	if (!ft_isalnum(s[i]) && s[i] != '_' && s[i] != '=') 
       	 return (1);
		i++;
	}
    return (0);
}
static void print_error(char *s1, char *s2, char *s3)
{
	ft_putstr(s1, 2);
	ft_putstr(s2, 2);
	ft_putstr(s3, 2);

}

static int	c_strncmp(const char *s1, const char *s2, char terminator)
{
        size_t  i;

        i = 0;
        if (!s1 || !s2)
                exit(-1);
        while(s1[i])
        {
			if (s1[i] == terminator && s2[i] != terminator)
				return (-1);
			if (s2[i] == terminator && s1[i] != terminator)
				return (1);
            if (s1[i] - s2[i])
                return (s1[i] - s2[i]);
            i++;
        }
        i--;
        return (s1[i] - s2[i]);
}
void	ft_putstr_quote(char *s)
{
	size_t	i = 0;
	int	found = 0;

	while (s[i])
	{
		if (!found && s[i] == '=')
		{
			write(1, &s[i], 1);
			write(1, "\"", 1);
			found = 1;
		}
		else
			write(1, &s[i], 1);
		i++;
	}
	(found) ? write(1, "\"\n", 2) : write(1, "\n", 1);
	/*if (found)
		write(1, "\"", 1);*/
	//write(1, quote, ft_strlen(quote));
}

static void print_the_envs(char **envp, int *sorted)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (envp[i])
	{
		j = 0;
		while (sorted[j] != (i + 1))
			j++;
		ft_putstr("declare -x ", 1);
		ft_putstr_quote(envp[j]);
		i++;
	}
}

/* this function needs to imitate the behaviour of export without any argument:
	It addds 'X- Declare to ever env name
	It sorts the variables in alphabetical order 
	It prints them after applying the above steps*/
void	no_args(char **envp)
{
	int		i, j, smallest;
	int		*sorted; // I need to change the starting point of the index from 0 to 1 cuz how would I know if 0 is alread sorted or not ?

	i = j = smallest =0;
	while (envp[j])
		j++;
	sorted = ft_calloc((j) * sizeof(int));
	//if (!sorted)
	//	exit(-1);// exit the program;
	while (envp[i])
	{
		j = smallest = 0;
		while (sorted[smallest]) // skips the string if It's already sorted,
			smallest++;
		while (envp[j])
		{
			if (!(sorted[j]) && (c_strncmp(envp[j], envp[smallest], '=') < 0)) // this line checks if the string is alread sorted if it is it skips it
				smallest = j;
			j++;
		}
		sorted[smallest] = i + 1;
		i++;
	}
	print_the_envs(envp, sorted);
	//free(sorted);
}
static int	ftc_strncmp(const char *s1, const char *s2)
{
    size_t  i;

    i = 0;
    while(s1[i] && s1[i] != '=')
    {
        if (s1[i] - s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
	if (!(s2[i]))
		return (0);
    return (s1[i] - s2[i]);
}
static int ft_var_exists(char *s, char **envp)
{
	size_t	i;
	size_t	size;
	char	*new;

	i = 0;
	size = 0;
	while (s[size] && s[size] != '=')
		size++;
	// if the exported variable exist in the environement file
	while (envp[i])
	{
		//if (!ft_strncmp(envp[i], s, size))
		if (!ftc_strncmp(s, envp[i]))
		{
			s = ft_strchr(s, '=');
			if (!s) // if the entered command doesn't include an '=' we shouldn't change the value that the var has;
				return (0);
			new = ft_strldup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
			new = ft_strjoinf(new, s);
			//free(envp[i]);
			envp[i] = new;
			//*status = 0;
			return (0);
		}
		i++;
	}
	return (1);
}
static char	**ft_duplicate_add_s(char **dup, char *s)
{
	char **p;
///	size_t		i = 0;
	size_t		size = 0;

///	p = ft_duplicate(dup, 1);
	// if (!p) ///////////////// CHECK FOR OTHER MALLOCS !!!!!!!!!!!!!!!
	// 	return (NULL);
	while(dup[size])
		size++;
	p = ft_calloc(sizeof(char *) * (size + 1));
	size = 0;
	while (dup[size])
	{
		p[size] = dup[size];
		size++;
	}
	p[size] = ft_strdup(s);
	//free(dup); // ft_malloc error
	/*while(p[i])
		i++;
	p[i] = ft_strdup(s);*/
	//free_all(dup);
	return (p);
}
char	**ft_export(char **argv, char **envp, unsigned char *status)
{
	size_t	ar = 1;
	//int		valid = 0;

	*status = 0;
	if (!argv[ar])
		return (*status = 0, no_args(envp), envp);
	while (argv[ar])
	{ 
		while (argv[ar] && (valid_var(argv[ar])))
		{
			print_error("minishell: export: `", argv[ar], "': not a valid identifier\n");
			*status = 1;
			ar++;
		}
		if (argv[ar] == NULL)
			return (envp);		
		if (ft_var_exists(argv[ar], envp)) // It has to have an equal '=' if we want to change the value of the given variable;
		{
			//*status = 0;
			envp = ft_duplicate_add_s(envp, argv[ar]); // copying the old variables and making space for the new one;
			if (!envp) ///////////////// CHECK FOR OTHER MALLOCS !!!!!!!!!!!!!!!
				return (*status = -1, NULL);
		}
		ar++;
	}
	return (envp);
}

char **ft_new_export(t_data *data)
{
	size_t	ar = 1;

	//data->rdl_args = c_split_02(data->dup_rdl,' ',data->envp,&data->status);
	data->status = 0;
	if (!data->rdl_args[ar])
		return (data->status = 0, no_args(data->envp), data->envp);
	while (data->rdl_args[ar])
	{ 
		while (data->rdl_args[ar] && (valid_var(data->rdl_args[ar])))
		{
			print_error("minishell: export: `", data->rdl_args[ar], "': not a valid identifier\n");
			data->status = 1;
			ar++;
		}
		if (data->rdl_args[ar] == NULL)
			return (data->envp);		
		if (ft_var_exists(data->rdl_args[ar], data->envp)) // It has to have an equal '=' if we want to change the value of the given variable;
		{
			//*status = 0;
			data->envp = ft_duplicate_add_s(data->envp, data->rdl_args[ar]); // copying the old variables and making space for the new one;
			if (!data->envp) ///////////////// CHECK FOR OTHER MALLOCS !!!!!!!!!!!!!!!
				return (data->status = -1, NULL);
		}
		ar++;
	}
	return (data->envp);
}