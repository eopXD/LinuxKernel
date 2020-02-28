#include <cstdio>
#include <cstdlib>

#include <algorithm>

using namespace std;

#include "natsort/strnatcmp.h"

static int compare_strings(const void *a, const void *b)
{
     char const *pa = *(char const **)a, *pb = *(char const **)b;
     int ret = strnatcmp(pa, pb);
     return ret;
}

int main () 
{
	int n;
	scanf("%d", &n);
	char ar[1003][1003];
	for ( int i=0; i<n; ++i ) {
		scanf("%s", ar[i]);
	}
	for ( int i=0; i<n; ++i ) {
		printf("%d: %s\n", i, ar[i]);
	}
	for ( int i=0; i<n; ++i ) {
		for ( int j=i+1; j<n; ++j ) {
			printf("%d %d XDDD\n", i, j);
			if ( compare_strings(ar[i], ar[j]) ) {
				swap(ar[i], ar[j]);
			}
		}
	}
	for ( int i=0; i<n; ++i ) {
		printf("%d: %s\n", i, ar[i]);
	}
	return 0;
}

