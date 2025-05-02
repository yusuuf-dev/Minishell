#include <stdio.h>

static int	c_strncmp(const char *s1, const char *s2, char terminator)
{
        size_t  i;

        i = 0;
        if (!s1 || !s2)
                return(-1);
        while(s1[i])
        {
			if (s1[i] == terminator && s2[i] != terminator)
				return (-1);
			if (s2[i] == terminator && s1[i] != terminator)
				return (1);
            if (s1[i] - s2[i])
                return (s1[i] - s2[i]);
            i++;
        }
        i--;
        return (s1[i] - s2[i]);
}

int main(void)
{
	char	*s1 = "GDMSESSION=ubuntu";
	char	*s2 = "GDM_LANG=en";

	printf("%d\n", c_strncmp(s1, s2, '='));
	return (0);
}
