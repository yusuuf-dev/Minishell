#include <stdio.h>

int main(void)
{
	int a = 5;
	int b = 10;

	// return is a statement, and ternary operator only work with expressions
	(a < b) ? (return (0)) : (return (-1));
}
