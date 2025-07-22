#include "../minishell.h"

/*int	ft_find(char **s, char *find, size_t *index)
{
	size_t	i = 0;
	size_t	size = ft_strlen(find);

	while (s[i])
	{
		if (!ft_strncmp(s[i], find, size))
		{
			*index = i;
			return (1);
		}
		i++;
	}
	return (0);
}*/
static  int    valid_var(char *s) // same function is used in ft_export
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

//void	query_envp(data->rdl_args[ar])

static void	remove_var_from_env(t_data *data, size_t ar)
{
	size_t	i;

	i = 0;
	while (data->envp[i]) // query the env
	{
		if (!c_strncmp(data->envp[i], data->rdl_args[ar]))
		{
			//free(envp[i]); // we use ft_malloc this is going to use a double free error,
			free_ft_malloc(data->envp[i], 1);
			while (data->envp[i])
			{
				data->envp[i] = data->envp[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}

int		ft_unset(t_data *data)
{
	size_t	ar = 1;
	size_t	i;

	// check if the arg is valid otherwise skip to the next arg set the exit status to 0;
	while (data->rdl_args[ar])
	{
		i = 0;
		if (data->rdl_args[ar] && valid_var(data->rdl_args[ar]))
			ar++;
		if (!data->rdl_args[ar])
			return (0);
		remove_var_from_env(data, ar);
		ar++;
	}
	// if found, free the string and move the other strings in the array starting from n to n-1, and set NULL to the last and the before-last string
	return (0);
}
/*
char	**ft_unset(char **argv, char **envp, unsigned char *status)
{
	char	**p = NULL;
	size_t	i = 0;
	size_t	size_env = 0;
	// the found variable indicates wether the passed argument exist in 
	// the environemet list
	size_t	ar = 1;
	// the index indicates the index of the passed argument in the list
	size_t	index = 0;

	while (argv[ar])
	{
		if (ft_find(envp, argv[ar], &index))
		{
			i = size_env = 0;
			while (envp[size_env])
				size_env++;
			p = ft_malloc(sizeof(char *) * (size_env + 1));
			p[size_env - 1] = NULL;
			size_env = 0;
			while (envp[i])
			{
				if (i != index)
				{
					p[size_env] = ft_strdup(envp[i]);
					size_env++;
				}
				i++;
			}
			//free_all(envp);
			envp = p;
			i = size_env = index = 0;
		}
		ar++;
	}
	*status = 0;
	return (envp);
}*/