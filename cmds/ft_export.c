/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:17:22 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/28 11:18:08 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_var_exists(char *s, char **envp)
{
	size_t	i;
	char	*new;

	i = 0;
	while (envp && envp[i])
	{
		if (!c_strncmp(s, envp[i]))
		{
			s = ft_strchr(s, '=');
			if (!s)
				return (0);
			new = ft_strldup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
			new = ft_strjoin(new, s);
			free_ft_malloc(envp[i], 1);
			envp[i] = ft_strdup_env(new);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**ft_duplicate_add_s(char **dup, char *s)
{
	char	**p;
	size_t	size;

	size = 0;
	while (dup && dup[size])
		size++;
	size = (sizeof(char *) * (size + 2));
	p = ft_malloc_env(size);
	ft_memset(p, 0, size);
	size = 0;
	while (dup && dup[size])
	{
		p[size] = dup[size];
		size++;
	}
	p[size] = ft_strdup_env(s);
	return (p);
}

char	**ft_new_export(t_data *data)
{
	size_t	ar;

	ar = 1;
	data->status = 0;
	if (!data->rdl_args[ar])
		return (print_env(data->envp, 0, 0, 0), data->envp);
	while (data->rdl_args[ar])
	{
		while (data->rdl_args[ar] && (valid_var(data->rdl_args[ar])))
		{
			ft_putstr("minishell: export: `", 2);
			ft_putstr(data->rdl_args[ar], 2);
			ft_putstr("': not a valid identifier\n", 2);
			data->status = 1;
			ar++;
		}
		if (data->rdl_args[ar] == NULL)
			return (data->envp);
		if (ft_var_exists(data->rdl_args[ar], data->envp))
		{
			data->envp = ft_duplicate_add_s(data->envp, data->rdl_args[ar]);
		}
		ar++;
	}
	return (data->envp);
}
