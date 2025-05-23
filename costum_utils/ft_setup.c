#include "../minishell.h"

void    config_rdline(char **p ,t_data *data)
{
    size_t  len;
    size_t  i;
    char    *new_p;

    len = ft_strlen(*p);
    new_p = ft_malloc(len + 1);
    i = 0;
    while (i < len)
    {
        new_p[i] = (*p)[i];
        i++;
    }
    new_p[i] = 0;
    free(*p);
    *p = NULL;
    data->p_rdl = new_p;
    data->rdl_args = c_split(new_p,' ');
    i = 0;
    while (data->rdl_args[i])
    {
        data->rdl_args[i] = rm_quotes_expand(data->rdl_args[i],data->envp,data->status);
        i++;
    }
}

// void       data_config(t_data *data)
// {
//     if (data->p_rdl)
//     {
//         data->rdl_args = c_split(p,' ');
//         i = 0;
//         while (data->rdl_args[i])
//         {
//             data->rdl_args[i] = rm_quotes_expand(data->rdl_args[i],envp,data->status);
//             i++;
//         }
//     }

// }

t_data     *ft_setup(char **envp)
{
    t_data  *data;
    char    *env;

    data = ft_malloc(sizeof(t_data));
    data->status = 0;
    data->exit = 0;
    data->p_rdl = NULL;
    data->envp = ft_duplicate(envp, 0);
    env = ft_getenv("PATH", data->envp, data->status);
	if (env)
    {
		data->env_paths = ft_split(env,':');
    }
    else
        data->env_paths = NULL;
    data->rdl_args = NULL;
    // data->rdl_args = c_split(p,' ');
    // i = 0;
    // while (data->rdl_args[i])
    // {
    //     data->rdl_args[i] = rm_quotes_expand(data->rdl_args[i],envp,data->status);
    //     i++;
    // }
    return(data);
}


