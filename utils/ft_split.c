/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:26 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/19 10:34:27 by yoel-you         ###   ########.fr       */
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
	int		i;

	i = 0;
	str = ft_malloc((ed - st + 1) * sizeof(char));
<<<<<<< HEAD
	if (!str)
		return (NULL);
=======
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	while (st < ed)
	{
		str[i++] = s[st++];
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char *str, char c)
{
	char	**ptr;
	int		i;
	int		j;
	int		st;
	int		wd;

<<<<<<< HEAD
	wd = ft_count_wd(str,c);
	ptr = ft_malloc((wd + 1) * sizeof(char*));
	if(!ptr)
		return(NULL);
=======
	wd = ft_count_wd(str, c);
	ptr = ft_malloc((wd + 1) * sizeof(char *));
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	i = 0;
	j = 0;
	while (str[i] && j < wd)
	{
		while (str[i] == c)
			i++;
		st = i;
		while (str[i] != c && str[i])
			i++;
		ptr[j] = ft_substr(str, st, i);
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}
