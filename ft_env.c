/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:00:03 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/11 15:26:51 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(int argc, char **argv, char **envp, char **envp_paths)
{
	size_t	i = 0;
//	size_t	size = 0;
	size_t	ar = 1;
	char	*path;
	int	status = 0;
	char	**new_envp = NULL;
	char	**new_arg = NULL;
	int	child_pid;
	int	child_info;

	(void)argc;
	if (!argv[ar])
	{
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
		return (0);
	}
	if (!ft_strchr(argv[ar], '='))
	{
		printf("Invalid argument\n");
		return (-1);
	}
	new_envp = ft_duplicate(envp);
	new_envp = ft_export(0, argv, new_envp, &status);
	while (argv[ar] && ft_strchr(argv[ar], '='))
		ar++;
	new_arg = ft_duplicate(&argv[ar]);
	child_pid = fork();
	if (!child_pid)
	{
		while (envp_paths[i])
		{
			path = ft_strjoinf(ft_strjoin(envp_paths[i], "/"), argv[ar]);
			if (execve(path, new_arg, new_envp) == -1)
			{
			//	printf("Error while executing execve\n");
			//	exit(-1);
			}
			free(path);
			i++;
		}
		exit (0);
	}
	else
	{
		if (child_pid < 0)
		{
			printf("error while creating a child\n");
			exit (-1);
		}
		wait(&child_info);
	}
	free_all(new_envp);
	free_all(new_arg);
	if (WIFEXITED(child_info))
		return (WEXITSTATUS(child_info));
	return (0);
}
