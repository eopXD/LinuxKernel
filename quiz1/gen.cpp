#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
	srand(time(NULL));
	int n = 50;
	printf("%d\n", n);
	for ( int i=0; i<n; ++i ) {
		printf("%d ", rand()%100);
	}
}