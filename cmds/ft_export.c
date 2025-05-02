/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:18:54 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/11 11:41:51 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isalnum(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	return (0);
}
static int	ft_isalpha(int c)
{
	if (c >= 97 && c <= 122)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	return (0);
}
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
	write(1, "\"\n", 2);
}

static void print_the_envs(char **envp, int *sorted, int size)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (sorted[j] != (i + 1))
			j++;
		ft_putstr("declare -x ", 1);
		ft_putstr_quote(envp[j]);
		i++;
	}
}

/* this functions need to imitate the behaviour of export without any argument:
	It addds 'X- Declare to ever env name
	It sorts the variables in alphabetical order 
	It prints them after applying the above steps*/
void	no_args(char **envp)
{
	int		i, j, smallest, size;
	int		*sorted; // I need to change the starting point of the index from 0 to 1 cuz how would I know if 0 is alread sorted or not ?

	i = j = smallest = size = 0;
	while (envp[size])
		size++;
	sorted = ft_calloc((size) * sizeof(int));
	if (!sorted)
		;// exit the program;
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
	print_the_envs(envp, sorted, size);
	free(sorted);
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
		if (!ft_strncmp(envp[i], s, size))
		{
			s = ft_strchr(s, '=');
			new = ft_strldup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
			new = ft_strjoinf(new, s);
			free(envp[i]);
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
	size_t		i = 0;

	p = ft_duplicate(dup, 1);
	if (!p) ///////////////// CHECK FOR OTHER MALLOCS !!!!!!!!!!!!!!!
		return (NULL);
	while(p[i])
		i++;
	p[i] = ft_strdup(s);
	free_all(dup);
	return (p);
}
char	**ft_export(int argc, char **argv, char **envp, int *status)
{
	size_t	ar = 1;

	(void)argc;
	if (!argv[ar])
		return (no_args(envp), envp);
	while (argv[ar])
	{ 
		while (argv[ar] && (valid_var(argv[ar]) || !(ft_strchr(argv[ar], '='))))
		{
			if (argv[ar] && valid_var(argv[ar])) // check for invalid variable name
			{
				print_error("minishell: export: `", argv[ar], "': not a valid identifier\n");
				*status = 1;
			}
			ar++;
		}
		if (argv[ar] == NULL)
			return (envp);		
		if (ft_var_exists(argv[ar], envp))
		{
			*status = 0;
			envp = ft_duplicate_add_s(envp, argv[ar]); // copying the old variables and making space for the new one;
			if (!envp) ///////////////// CHECK FOR OTHER MALLOCS !!!!!!!!!!!!!!!
				return (*status = -1, NULL);
		}
		ar++;
	}
	return (envp);
}
