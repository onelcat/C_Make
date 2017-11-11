#include <stdio.h>


typedef struct persion
{
	persion * p;
}persion;

int main(int argc, char const *argv[])
{
	int s = sizeof(int);
	printf("%d\n", s);
	s = 0;
	int b = 1 << 6 | 1 << 5 | 1 << 4 | 1 << 3 | 1 << 2 | 1 << 1 | 1;
	// b = 1 << 5 | b;
	printf("%x\n", b);
    int a = (b >> 5) & 0x1;
    printf("%d\n", a);
	return 0;
}