/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:00:05 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/18 18:18:58 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*charjoin(char *s1, char c)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	if (!c)
		return (s1);
	len = ft_strlen(s1);
	ptr = ft_malloc((len + 2) * sizeof(char));
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = c;
	ptr[i] = 0;
	return (ptr);
}

static void	add_ptr(char **ptr, t_data *data, int i, int j)
{
	char	**ptrs;

	if (*ptr == NULL)
		return ;
	i = 0;
	while (data->rdl_args && data->rdl_args[i])
		i++;
	ptrs = ft_malloc((i + 2) * sizeof(char *));
	j = 0;
	while (j < i)
	{
		ptrs[j] = data->rdl_args[j];
		j++;
	}
	ptrs[j++] = ft_strdup(*ptr);
	ptrs[j] = NULL;
	if (data->rdl_args)
	{
		data->rdl_args = ptrs;
	}
	else
		data->rdl_args = ptrs;
	*ptr = NULL;
}

static char	*expand_join(char *str, t_data *data, size_t index, size_t *expand)
{
	char	*new;
	char	*key;
	char	*var;
	size_t	i;
	size_t	len;

	len = 0;
	i = index + 1;
	len = getlen_helper(str, i);
	key = ft_strldup(str + i, len);
	if (ft_strcmp(key, "?"))
		var = ft_getenv("?", data->envp, &data->status);
	else
		var = ft_getenv(key, data->envp, &data->status);
	if (var)
	{
		new = ft_strjoin(ft_strldup(str, index), var);
		new = ft_strjoin(new, ft_strldup(str + i + len, ft_strlen(str + i)));
		*expand += ft_strlen(var);
	}
	else
		new = joinstr_helper(str, i, len, index);
	return (new);
}

static void	get_argements(char *str, char *checker, t_data *data)
{
	char	*ptr;
	size_t	i;
	char	q;

	q = 0;
	i = 0;
	ptr = NULL;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (checker[i] == '0' && !q && (str[i] == '\"' || str[i] == '\''))
			q = str[i];
		else if (checker[i] == '0' && q && str[i] == q)
			q = 0;
		else
			ptr = charjoin(ptr, str[i]);
		i++;
		if (ptr && !q && (str[i] == ' ' || !str[i]))
		{
			add_ptr(&ptr, data, 0, 0);
			while (str[i] == ' ')
				i++;
		}
	}
}

void	custom_split(char *str, t_data *data, size_t i, char q)
{
	size_t	is_exp;

	data->expand = NULL;
	data->checker = NULL;
	is_exp = 0;
	while (str[i])
	{
		if (!is_exp && !q && (str[i] == '\'' || str[i] == '\"'))
			q = str[i];
		else if (!is_exp && q && str[i] == q)
			q = 0;
		while (q != '\'' && str[i] == '$' && validchar_helper(str[i + 1]))
			str = expand_join(str, data, i, &is_exp);
		if (!str[0])
			return;
		data->expand = charjoin(data->expand, str[i]);
		if (!str[i])
			break;
		if (is_exp)
			data->checker = charjoin(data->checker, '1');
		else
			data->checker = charjoin(data->checker, '0');
		i++;
		if (is_exp)
			is_exp--;
	}
	get_argements(data->expand, data->checker, data);
}
