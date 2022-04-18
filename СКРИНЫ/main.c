#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, const char *argv[]) {
    char *s = malloc(100);
	s = "Hello";
    printf("string is: %s\n", s);
	free(s);
    return 0;
}
