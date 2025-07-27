/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:08:11 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/15 10:08:12 by yoel-you         ###   ########.fr       */
=======
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:08:11 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 12:15:58 by yoel-you         ###   ########.fr       */
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
void    *get_data(void *p)
{
    static void *ptr;

    if (p)
        ptr = p;
    return (ptr);
}
static int assign_std_in_out_err(t_data *data)
{
    data->fd0 = dup(STDIN_FILENO);
    if (data->fd0 == -1)
        return (perror(""), 1);
    data->fd1 = dup(STDOUT_FILENO);
    if (data->fd1 == -1)
        return (close(data->fd0), perror(""), 1);
    data->fd2 = dup(STDERR_FILENO);
    if (data->fd2 == -1)
        return (close(data->fd0), close(data->fd1), perror(""), 1);
    return (0);
}

static char *get_cwd(t_data *data)
{
    char    *p;
    char    *temp;
    char    *var_pwd;

    p = NULL;
	p = getcwd(p, 0);
	if (!p)
		return (perror("getcwd"), NULL);
    temp = p;
    p = ft_strdup_env(p);
    free(temp);
    var_pwd = ft_strjoin("PWD=", p);
=======
void	*get_data(void *p)
{
	static void	*ptr;

	if (p)
		ptr = p;
	return (ptr);
}

static int	assign_std_in_out_err(t_data *data)
{
	data->fd0 = dup(STDIN_FILENO);
	if (data->fd0 == -1)
		return (perror(""), 1);
	data->fd1 = dup(STDOUT_FILENO);
	if (data->fd1 == -1)
		return (close(data->fd0), perror(""), 1);
	data->fd2 = dup(STDERR_FILENO);
	if (data->fd2 == -1)
		return (close(data->fd0), close(data->fd1), perror(""), 1);
	return (0);
}

static char	*get_cwd(t_data *data)
{
	char	*p;
	char	*temp;
	char	*var_pwd;

	p = NULL;
	p = getcwd(p, 0);
	if (!p)
		return (perror("getcwd"), NULL);
	temp = p;
	p = ft_strdup_env(p);
	free(temp);
	var_pwd = ft_strjoin("PWD=", p);
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
	if (ft_var_exists(var_pwd, data->envp))
	{
		data->envp = ft_duplicate_add_s(data->envp, var_pwd);
	}
<<<<<<< HEAD
    return (p);
}

void    ft_setup(t_data *data, char **envp, int ac, char **av)
{
  //  char    *env;

    (void)envp;
    (void)ac;
    (void)av;
    get_data(data);
    ft_memset(data, 0, sizeof(t_data));
    if (assign_std_in_out_err(data))
      exit(errno);
    data->envp = ft_duplicate(__environ, 0);
    if (!data->envp)
    {
        perror("");
        exit (errno);
    }
    data->cwd = get_cwd(data);
   /* env = ft_getenv("PATH", data->envp, &(data->status));
	if (env)
		data->env_paths = ft_split(env, ':');*/
    
    /* SIG QUIT*/
    sigemptyset(&(data->S_SIG_IGN.sa_mask));
    data->S_SIG_IGN.sa_flags = SA_RESTART;
    data->S_SIG_IGN.sa_handler = SIG_IGN;
    /* SIG INT*/
    sigemptyset(&(data->SIG_INT.sa_mask));
    data->SIG_INT.sa_flags = SA_RESTART;
    data->SIG_INT.sa_handler = signal_handler;

    /* DFL*/
    sigemptyset(&(data->S_SIG_DFL.sa_mask));
    data->S_SIG_DFL.sa_flags = SA_RESTART;
    data->S_SIG_DFL.sa_handler = SIG_DFL;
    /* setting the signal handlers and saving the old ones */
    sigaction(SIGINT, &(data->SIG_INT), &(data->OLD_SIG_INT));
   	sigaction(SIGQUIT, &(data->S_SIG_IGN), &(data->OLD_SIG_QUIT));
    return ;

=======
	return (p);
}

void	ft_setup(t_data *data)
{
	char	**built_ins;

	get_data(data);
	ft_memset(data, 0, sizeof(t_data));
	if (assign_std_in_out_err(data))
		exit(errno);
	data->envp = ft_duplicate(__environ);
	built_ins = ft_split("pwd,cd,export,echo,env,unset,exit", ',');
	data->built_ins = ft_duplicate(built_ins);
	data->cwd = get_cwd(data);
	sigemptyset(&(data->s_sig_ign.sa_mask));
	data->s_sig_ign.sa_flags = SA_RESTART;
	data->s_sig_ign.sa_handler = SIG_IGN;
	sigemptyset(&(data->sig_int.sa_mask));
	data->sig_int.sa_flags = SA_RESTART;
	data->sig_int.sa_handler = signal_handler;
	sigemptyset(&(data->s_sig_dfl.sa_mask));
	data->s_sig_dfl.sa_flags = SA_RESTART;
	data->s_sig_dfl.sa_handler = SIG_DFL;
	sigaction(SIGINT, &(data->sig_int), &(data->old_sig_int));
	sigaction(SIGQUIT, &(data->s_sig_ign), &(data->old_sig_quit));
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
}
