#include <stdio.h>

void debugger(unsigned char *start, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf(" %.2x", start[i]);
	printf("\n");
}

int main()
{
  int i = 0x01234567;
  debugger((unsigned char *)&i, sizeof(i)); // prints 67 45 23 01 in little-endian computer
  getchar();
  return 0;
}
