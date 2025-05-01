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

static char	**ft_duplicate_add_s(char **dup, char *s);
static int ft_var_exists(char *s, char **envp);

static void print_error(char *s1, char *s2, char *s3)
{
	ft_putstr(s1, 2);
	ft_putstr(s2, 2);
	ft_putstr(s3, 2);

}

void	no_args(char **envp)
{
	// this functions need to imitate the behaviour of export without any argument:
		//It addds 'X- Declare to ever env name
		// It sorts the variables in alphabetical order 
		// It prints them after applying the above steps

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
				print_error("minishell: export: `", argv[ar], "': not a valid identifier\n");
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
