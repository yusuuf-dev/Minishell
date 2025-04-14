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

char	**ft_export(int argc,char **argv, char **envp, int *status)
{
	char	**p;
	char	*s;
	char	*new;
	int	size;
	size_t	i;
	size_t	ar = 1;
	int	found = 0;

	(void)argc;
	while (argv[ar])
	{ 
		while (argv[ar] && !(ft_strchr(argv[ar], '=')))
			ar++;
		if (argv[ar] == NULL)
			return (envp);
		i = 0;
		size = 0;
		s = argv[ar];
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
				*status = 0;
				found = 1;
			}
			i++;
		}
	// copying the old variables and making space for the new one;
		if (!found)
		{
			size = 0;
			while (envp[size])
				size++;
			p = malloc(sizeof(char *) * (size + 2));
			if (!p) ///////////////// CHECK FOR OTHER MALLOCS !!!!!!!!!!!!!!!
			{
				*status = -1;
				return (NULL);
			}
			p[size + 1] = NULL;
			size = 0;
			while (envp[size])
			{
				p[size] = ft_strdup(envp[size]);
				size++;
			}
			p[size] = ft_strdup(s);
			*status = 0;
			free_all(envp);
			envp = p;
		}
		found = 0;
		ar++;
	}
	return (envp);
}
