/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:17:31 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/20 16:05:16 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_count_wd(char *s, char c)
{
	size_t	i;
	size_t	count;
	char	q;

	i = 0;
	count = 0;
	q = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			q = s[i++];
			if (s[i] != q)
				count++;
			while (s[i] != q)
				i++;
			q = 0;
		}
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_substr(char *s, int st, int ed)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_malloc((ed - st + 1) * sizeof(char));
	while (st < ed)
	{
		str[i++] = s[st++];
	}
	str[i] = '\0';
	return (str);
}

static size_t	skip_quotes(char *str, char c, size_t i)
{
	char	q;

	q = 0;
	while (str[i] != c && str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			q = str[i];
			i++;
			while (str[i] != q)
				i++;
		}
		i++;
	}
	return (i);
}

char	**c_split(char *str, char c)
{
	char	**ptr;
	size_t	wd;
	size_t	st;
	size_t	j;
	size_t	i;

	wd = ft_count_wd(str, c);
	ptr = ft_malloc((wd + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (str[i] && j < wd)
	{
		while (str[i] == c)
			i++;
		st = i;
		i = skip_quotes(str, c, i);
		ptr[j] = ft_substr(str, st, i);
		if (ptr[j])
			j++;
	}
	ptr[j] = NULL;
	return (ptr);
}