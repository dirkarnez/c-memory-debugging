#include <stdio.h>
#include <stdint.h>

void debugger(void *start, int size)
{
    unsigned char *ptr = start;
	for (int i = 0; i < size; i++){
        printf(" %.2x", (unsigned char)(*(ptr + i)));
        if (i % 16 == 15) {
            printf("\n");
        }
    }
	printf("\n");
}

void *my_memset(void *b, int c, int len)
{
  if (b == NULL || len < 0) {
    return b;
  }

  unsigned char *ptr = b;
  while(*ptr != '\0' && len--)
  {
    *ptr++ = (unsigned char)c;
  }

  return(b);
}


struct dylinker_command_for_dyld_only {
	uint32_t	cmd;		/* LC_ID_DYLINKER, LC_LOAD_DYLINKER or
					   LC_DYLD_ENVIRONMENT */
	uint32_t	cmdsize;	/* includes pathname string */
    uint32_t offset_in_bytes_hardcode_to_12; //
	uint8_t  name[20];		/* dynamic linker's path name */
};


int main()
{
    struct dylinker_command_for_dyld_only dyld;
    my_memset(&dyld, 0, sizeof(struct dylinker_command_for_dyld_only));
    dyld.cmd = 14U;
    dyld.cmdsize = sizeof(struct dylinker_command_for_dyld_only); // constant
    dyld.offset_in_bytes_hardcode_to_12 = 12; // constant
    dyld.name[0] = '/';
    dyld.name[1] = 'u';
    dyld.name[2] = 's';
    dyld.name[3] = 'r';
    dyld.name[4] = '/';
    dyld.name[5] = 'l';
    dyld.name[6] = 'i';
    dyld.name[7] = 'b';
    dyld.name[8] = '/';
    dyld.name[9] = 'd';
    dyld.name[10] = 'y';
    dyld.name[11] = 'l';
    dyld.name[12] = 'd';
    dyld.name[13] = '\0';

  int i = 0x01234567;
  debugger(&i, sizeof(int)); // prints 67 45 23 01 in little-endian computer
  printf("\n");
  debugger(&dyld, sizeof(struct dylinker_command_for_dyld_only)); // prints 67 45 23 01 in little-endian computer
  getchar();
  return 0;
}
