/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:23:00 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/13 10:57:07 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static ssize_t only_parm(char *s)
{
    size_t  i;
    ssize_t     status;

    i = 0;
    status = 0;
    while (s[i])
    {
        if (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
            i++;
        else if (s[i] == '-' && s[i + 1] == 'n')
        {
            i++;
            while (s[i] == 'n')
                i++;
            if (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
            {
                if (status == 0)
                    return (-1);
                else
                    return(0);
            }
            else
                status = 1;    
        }
        else
        {
            if (status == 0)
                return (1);
            return(0);
        }
    }
    return(1);
}

static ssize_t skip_parm(char *s)
{
    ssize_t  i;
    ssize_t  j;

    i = 0;
    while (s[i])
    {
        if(s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
            i++;
        else if (s[i] == '-' && s[i + 1] == 'n')
        {
            j = 1;
            while(s[i + j] == 'n')
                j++;
            if (s[i + j] == ' ' || (s[i + j] >= 9 && s[i + j] <= 13))
                i +=j;
            else
                return(i); 
        }
        else
            return(i);
    }
    return(1);
}

static char	*ft_substrf(char *s, int st, int ed)
{
	char	*str;
	int	i;

	i = 0;
	str = malloc((ed - st + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (st < ed)
	{
		str[i++] = s[st++];
	}
	str[i] = '\0';
    free(s);
	return (str);
}

int     ft_echo( char **p)
{
	size_t	i;
    ssize_t  status;

    i = 1;
    status = 0;
    while (p[i])
    {
        status = only_parm(p[i]);
        if (status == -1)
            break;
        else if (status == 1)
            i++;
        else 
        {
            status = skip_parm(p[i]);
            if (status > 1)
            {
                p[i] = ft_substrf(p[i],status,ft_strlen(p[i]));
                break;
            }
            else
                break;
        }
    }
    while (p[i])
    {
        printf("%s",p[i]);
        if(p[i + 1])
            printf(" ");
        i++;
    }
    if(!p[1] || status < 1)
	{
    	printf("\n");
	}
	return (0);
}

