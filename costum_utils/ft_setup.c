/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:08:11 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/15 10:08:12 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void    ft_setup(t_data *data, char **envp)
{
  //  char    *env;

    (void)envp;
    ft_memset(data, 0, sizeof(t_data));
    data->envp = ft_duplicate(__environ, 0);
    if (!data->envp)
    {
        perror("");
        exit (errno);
    }
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

    /* setting the signal handlers and saving the old ones */
    sigaction(SIGINT, &(data->SIG_INT), &(data->OLD_SIG_INT));
   	sigaction(SIGQUIT, &(data->S_SIG_IGN), &(data->OLD_SIG_QUIT));
    return ;

}