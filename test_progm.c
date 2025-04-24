#include <unistd.h>
#include <string.h>

int	main(void)
{
	char s[] = "testing fddddddddddddddddd something";
	s[0] = 'A';
	write(33, s, sizeof(s));
	return (0);
}
