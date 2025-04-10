/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:18:54 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/10 15:46:45 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_export(int argc,char **argv, char **envp, int *status)
{
	char **temp;
	char	**p;
	char	*s;
	char	*new;
	char	*t = NULL;
	int	size;
	size_t	i;
	size_t	ar = 0;
	int	found = 0;
	int	change = 0;

	i = 0;
	size = 0;
	temp = envp;
	(void)argc;
		//return (*envp);
//	if (!ft_strchr(p1, '='))
//		return (*envp);
//	s = ft_strchr(p1, ' ') + 1;
	while (argv[ar] && !(ft_strchr(argv[ar], '=')))
		ar++;
	while (argv[ar])
	{ 
		s = argv[ar];
		while (s[size] && s[size] != '=')
			size++;
	// if the exported variable exist in the environement file
		while (temp[i])
		{
			if (!ft_strcmp(temp[i], s, size))
			{
				s = ft_strchr(s, '=');
			/*	if (ft_strchr(s, ' '))
					t = ft_strldup(s, ft_strchr(s, ' ') - s);
				else
					t = ft_strdup(s);*/
				new = ft_strldup(temp[i], ft_strchr(temp[i], '=') - temp[i]);
				new = ft_strjoinf(new, t);
				free(t);
			//	free(temp[i]); the environement is not stored in the heap :)
			//	what if I allocated the environement in the heap ???
				temp[i] = new;
				*status = 0;
				found = 1;
			//	return (temp);
			}
			i++;
		}
	// copying the old variables and making space for the new one;
		if (!found)
		{
			change = 1;
			size = 0;
			while (temp[size])
				size++;
			p = malloc(sizeof(char *) * (size + 2));
			if (!p) ///////////////// CHECK FOR OTHER MALLOCS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			{
				*status = -1;
				return (NULL);
			}
			p[size + 1] = NULL;
			size = 0;
			while (temp[size])
			{
				p[size] = ft_strdup(temp[size]);
				size++;
			}
			if (ft_strchr(s, ' '))
				p[size] = ft_strldup(s, ft_strchr(s, ' ') - s);
			else
				p[size] = ft_strdup(s);
			*status = 0;
			found = 0;
		}
		ar++;
	}
	if (change)
		return (p);
	else
		return (temp);
//	envp = &p;
}
