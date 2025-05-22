/* this is not needed anymore, I think*/
static int ft_isdigit(int n)
{
    if (n >= 48 && n <= 57)
        return (1);
    return (0);
}
int costum_atoi(char *nptr, unsigned char *status, int fd)
{
    int     i;
	long    rslt;

	i = 0;
	rslt = 0;
    if (!nptr || !nptr[0])
    {    return (1);}
	while (nptr[i])
	{
        if (ft_isdigit(nptr[i]))
        {
            if (rslt >= 2147483647)
                return (*status = 2, fd); // the return used to be '2';
		    rslt = rslt * 10;
		    rslt = rslt + (nptr[i] - 48);
        }
        else
            return (*status = 2, fd); // the return used to be '2';
        i++;
	}
    if (rslt > 2147483647)
        {return (*status = 2, fd);}
	return (rslt);
}