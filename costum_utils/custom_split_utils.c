/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:04:57 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/21 18:02:20 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validchar_helper(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

size_t	getlen_helper(char *str, size_t index)
{
	size_t	len;

	len = 0;
	if (str[index] == '?')
		return (1);
	while (str[index + len])
	{
		if (ft_isalnum(str[index + len]))
			len++;
		else if (str[index + len] == '_')
			len++;
		else
			break ;
	}
	return (len);
}

char	*joinstr_helper(char *str, size_t i, size_t len, size_t index)
{
	char	*s1;
	char	*s2;
	char	*ptr;

	s1 = ft_strldup(str, index);
	s2 = ft_strldup(str + i + len, ft_strlen(str + i + len));
	ptr = ft_strjoin(s1, s2);
	return (ptr);
}
