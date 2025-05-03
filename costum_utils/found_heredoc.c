
#include "../minishell.h"

int     found_heredoc(char *s)
{
    size_t i = 0;
    char    q = 0;

    while (s[i])
    {
        if (!q && (s[i] == '\"' || s[i] == '\''))
            q = s[i];
        else if (!q && s[i] == '<' && s[i + 1] ==  '<')
        {
            if (!s[i + 2] || s[i + 2] == '<' || s[i + 2] == '>')
                return(ft_putstr("minishell: syntax error near unexpected token `newline'\n", 2), -1);
            i += 2;
            while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
                i++;
            if (!s[i])
                return(-1); // if there's nothing after << must handle it like bash: syntax error near unexpected token `newline'            
            else
            {
               // if (!(s[i + 1]))
             //
             
             
             
                return(1);

            }
        }
        else if (s[i] == q)
            q = 0;
        i++;
    }
    return(0);
}