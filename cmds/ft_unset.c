#include "../minishell.h"

int	ft_find(char **s, char *find, size_t *index)
{
	size_t	i = 0;
	size_t	size = ft_strlen(find);

	while (s[i])
	{
		if (!ft_strncmp(s[i], find, size))
		{
			*index = i;
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_unset(char **argv, char **envp, unsigned char *status)
{
	char	**p = NULL;
	size_t	i = 0;
	size_t	size_env = 0;
	// the found variable indicates wether the passed argument exist in 
	// the environemet list
	size_t	ar = 1;
	// the index indicates the index of the passed argument in the list
	size_t	index = 0;

	while (argv[ar])
	{
		if (ft_find(envp, argv[ar], &index))
		{
			i = size_env = 0;
			while (envp[size_env])
				size_env++;
			p = ft_malloc(sizeof(char *) * (size_env + 1));
			p[size_env - 1] = NULL;
			size_env = 0;
			while (envp[i])
			{
				if (i != index)
				{
					p[size_env] = ft_strdup(envp[i]);
					size_env++;
				}
				i++;
			}
			// free_all(envp);
			envp = p;
			i = size_env = index = 0;
		}
		ar++;
	}
	*status = 0;
	return (envp);
}