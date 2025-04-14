/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:18:43 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/14 09:18:43 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_count_wd(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_substr(char *s, int st, int ed)
{
	char	*str;
	int	i;

	i = 0;
	str = malloc((ed - st + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (st < ed)
	{
		str[i++] = s[st++];
	}
	str[i] = '\0';
	return (str);
}

char	**free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return(NULL);
}

char	**ft_split(char *str, char c)
{
	char	**ptr;
	int	i;
	int	j;
	int	st;
	int	wd;

	wd = ft_count_wd(str,c);
	ptr = malloc((wd + 1) * sizeof(char*));
	if(!ptr)
		return(NULL);
	i = 0;
	j = 0;
	while (str[i] && j < wd)
	{
		while (str[i] == c)
			i++;
		st = i;
		while (str[i] != c && str[i])
			i++;
		ptr[j] = ft_substr(str,st,i);
		if (!ptr[j++])
			return(free_all(ptr));
	}
	ptr[j] = NULL;
	return (ptr);
}
