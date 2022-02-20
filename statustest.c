#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
int main(int argc, char** argv)
{
	int res = atoi(argv[1]);
	printf("atoi = %d\n", res);
	exit(res);
}	
