#include "../minishell.h"
/*
static void			ft_space(char *s)
{
	size_t	i = 0;
	int		f_s = 0;
	int		f_d = 0;

	while(s[i])
	{
		if(s[i] == '\'' && !f_d)
			f_s = !f_s;
		if(s[i] == '\"' && !f_s)
			f_d = !f_d;
		if(!f_d && !f_s && s[i] >= 9 && s[i] <= 13)
			s[i] = ' ';
		i++;
	}
}

void    config_rdline(char **p ,t_data *data)
{
    size_t  len;
    size_t  i;
    char    *new_p;

    len = ft_strlen(*p);
    new_p = ft_calloc(len + 1);
    i = 0;
    while (i < len)
    {
        new_p[i] = (*p)[i];
        i++;
    }
    new_p[i] = 0;
    free(*p);
    *p = NULL;
    //data->p_rdl = new_p;
    data->p_rdl = *p;
    ft_space(data->p_rdl); 
    data->rdl_args = c_split(*p, ' ');
    i = 0;
    while (data->rdl_args[i])
    {
        data->rdl_args[i] = rm_quotes_expand(data->rdl_args[i],data->envp,data->status);
        i++;
    }
}*/

void    ft_setup(t_data *data, char **envp)
{
    (void)envp;
    ft_memset(data, 0, sizeof(t_data));
    data->envp = ft_duplicate(__environ, 0);
    if (!data->envp)
    {
        perror("");
        exit (errno);
    }
    sigemptyset(&(data->C_slash.sa_mask));
    data->C_slash.sa_flags = 0; // change me to SA_RESTART
    data->C_slash.sa_handler = SIG_IGN;
    sigemptyset(&(data->C_c.sa_mask));
    data->C_c.sa_flags = SA_RESTART;
    data->C_c.sa_handler = signal_handler;
	sigemptyset(&(data->C_c_alt.sa_mask));
	data->C_c_alt.sa_flags = SA_RESTART; // change me to SA_RESTARt
    data->C_c_alt.sa_handler = count_sigs;
    return ;
}
/*t_data     *ft_setup(char **envp)
{
    t_data  *data;
    char    *env;

   // data = ft_malloc(sizeof(t_data));
    data = ft_calloc(sizeof(t_data));
    data->envp = ft_duplicate(envp, 0);
    env = ft_getenv("PATH", data->envp, data->status);
	if (env)
    {
		data->env_paths = ft_split(env,':');
    }
    else
        data->env_paths = NULL;
    data->rdl_args = NULL;
    return(data);
}*/