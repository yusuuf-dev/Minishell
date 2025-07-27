/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:57:39 by asoufian          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/24 09:33:56 by asoufian         ###   ########.fr       */
=======
/*   Updated: 2025/07/24 14:33:36 by yoel-you         ###   ########.fr       */
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*update_env_pwd(t_data *data, char *argv_bkp)
{
	char	*p;
	char	*var_pwd;
	char	*var_oldpwd;

	p = NULL;
	var_oldpwd = ft_strjoin("OLDPWD=", data->cwd);
	if (ft_var_exists(var_oldpwd, data->envp))
		data->envp = ft_duplicate_add_s(data->envp, var_oldpwd);
	p = getcwd(p, 0);
	if (!p)
	{
		perror("getcwd");
		p = ft_strjoin(data->cwd, argv_bkp);
	}
	var_pwd = p;
	p = ft_strdup(var_pwd);
	free(var_pwd);
	free_ft_malloc(data->cwd, 1);
	data->cwd = ft_strdup_env(p);
	var_pwd = ft_strjoin("PWD=", data->cwd);
	if (ft_var_exists(var_pwd, data->envp))
		data->envp = ft_duplicate_add_s(data->envp, var_pwd);
	return (data->cwd);
}

static int	var_not_set(char **argv, char *argv_bkp)
{
	if (argv[1] == NULL && (argv_bkp == NULL || ft_check_spaces(argv_bkp)))
		return (ft_putstr("minishell: cd: HOME not set\n", 2), 1);
	if (argv[1] == NULL && argv_bkp[0] == '-' && !argv_bkp[1])
		return (ft_putstr("minishell: cd: OLDPWD not set\n", 2), 1);
	return (0);
}

static int	search_cdpath_var(char **argv, char **envp)
{
	char	*cdpath;
	char	**paths;
	char	*try_dir;
	size_t	i;

	cdpath = ft_getenv("CDPATH", envp, NULL);
	if (!cdpath)
		return (0);
	paths = ft_split(cdpath, ':');
	i = 0;
	while (paths && paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
			paths[i] = ft_strjoin(paths[i], "/");
		try_dir = ft_strjoin(paths[i], argv[1]);
		if (!chdir(try_dir))
			return (ft_putstr(try_dir, 1), write(1, "\n", 1), 1);
		i++;
	}
	return (0);
}

int	ft_cd(char **argv, char *argv_bkp, t_data *data, bool exists_in_cdpath)
{
	char	*var_pwd;

	if (argv[1] && argv[2] != NULL)
		return (ft_putstr("minishell: cd: too many arguments\n", 2), 1);
	if (argv[1] && argv[1][0] == '-' && !argv[1][1])
		argv[1] = ft_getenv("OLDPWD", data->envp, NULL);
	else if (!argv[1] || ft_check_spaces(argv[1]))
		argv[1] = ft_getenv("HOME", data->envp, NULL);
	else if (argv[1][0] != '/' && argv[1][0] != '.')
		exists_in_cdpath = search_cdpath_var(argv, data->envp);
	if (var_not_set(argv, argv_bkp))
		return (argv[1] = argv_bkp, 1);
	if (!exists_in_cdpath && chdir(argv[1]))
	{
		var_pwd = ft_strjoin(ft_strjoin("minishell : cd: ", argv[1]), ": ");
		var_pwd = ft_strjoin(var_pwd, strerror(errno));
		ft_putstr(var_pwd, 2);
		return (ft_putstr("\n", 2), argv[1] = argv_bkp, 1);
	}
	var_pwd = update_env_pwd(data, argv_bkp);
	if (!var_pwd)
		return (argv[1] = argv_bkp, perror("minishell: cd: "), errno);
	if (argv_bkp && argv_bkp[0] == '-' && argv_bkp[1] == 0)
		ft_putstr(ft_strjoin(var_pwd, "\n"), 1);
	return (argv[1] = argv_bkp, 0);
}
