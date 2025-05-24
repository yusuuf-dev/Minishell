#include "../minishell.h"

char	*update_env_pwd(char **pwd_variable, char ***envp, unsigned char *status);
int		search_cdpath_var(char **argv, char ***envp, char **pwd_variable);

int     ft_cd(char **argv, char ***envp)
{
	char	**pwd_variable;
	char	*p = NULL;
	char	*t = NULL;
	int		f = 0;
	unsigned char	status;	// this does nothing yet


	if (argv[1] && argv[2] != NULL) // if we have more than 1 argument, the program returns error
		return (ft_putstr("minishell: cd: too many arguments\n", 2), 1);
	t = argv[1]; // this is for when we want to use the $HOME env variable
	pwd_variable = ft_calloc(sizeof (char *) * 4);
	// pwd_variable[4] = argv[1]; // remember to change the allocation above if you want to uncomment this line
	if (!pwd_variable)
		exit (-1); // free ?
	//p = getcwd(p, 4100);
	p = getcwd(p, 0);
	if (!p)
		return (perror("cd"), free(pwd_variable), errno);
	pwd_variable[1] = ft_strjoin("OLDPWD=", p);
	free(p);
	if (argv[1] && argv[1][0] == '-' && ft_check_spaces(&argv[1][1]))
		argv[1] = ft_getenv("OLDPWD", *envp, NULL);	
	else if (!argv[1] || ft_check_spaces(argv[1])) // || (argv[1][0] == '~' && !argv[1][1])): I don't need this here cuz the '~' gets handled in the parsing part
		argv[1] = ft_getenv("HOME", *envp, NULL); // I don't need to do this cuz the expansion happens in the parsin part of the shell;
	else if (argv[1][0] != '/' && argv[1][0] != '.')	
		f = search_cdpath_var(argv, envp, pwd_variable);
	if (argv[1] == NULL && (t == NULL || ft_check_spaces(t)))
		return (ft_putstr("minishell: cd: HOME not set\n", 2), argv[1] = t, free(pwd_variable[1]), free(pwd_variable), 1);
	if (argv[1] == NULL && t[0] == '-')
		return (ft_putstr("minishell: cd: OLDPWD not set\n", 2), argv[1] = t, free(pwd_variable[1]), free(pwd_variable), 1);
	if (!f && chdir(argv[1]))
		return (argv[1] = t, perror("cd"), free(pwd_variable[1]), free(pwd_variable), 1);
	p = update_env_pwd(pwd_variable, envp, &status);
	if (!p)
		return (argv[1] = t, perror("cd"), free(pwd_variable[1]), free(pwd_variable), errno);
	if (t && t[0] == '-' && ft_check_spaces(&t[1]))
		printf("%s\n", (ft_strchr(pwd_variable[2], '=') + 1));
	return (argv[1] = t, free(p), free(pwd_variable[1]), free(pwd_variable[2]), free(pwd_variable), 0);
}

int	search_cdpath_var(char **argv, char ***envp, char **pwd_variable)
{
	char	*cdpath = NULL;
	char	**paths = NULL;
	char	*try_dir = NULL;
	size_t	i = 0;

	(void)pwd_variable;
	cdpath = ft_getenv("CDPATH", *envp, NULL);
	if (!cdpath)
		return (0);
	paths = ft_split(cdpath, ':');
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
			paths[i] = ft_strjoinf(paths[i], "/");
		try_dir = ft_strjoin(paths[i], argv[1]);
		if (!chdir(try_dir))
			return (printf("%s\n", try_dir), free(try_dir), free_all(paths), 1);
		free(try_dir);
		i++;
	}
	free_all(paths);
	return (0);
}

char	*update_env_pwd(char **pwd_variable, char ***envp, unsigned char *status)
{
	char	*p = NULL;

	*envp = ft_export(pwd_variable, *envp, status);
	//p = getcwd(p, 4100);
	p = getcwd(p, 0);
	if (!p)
		return (NULL);
	pwd_variable[2] = ft_strjoin("PWD=", p);
	*envp = ft_export(&pwd_variable[1], *envp, status);
	return (p);
}