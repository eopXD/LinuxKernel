#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "strnatcmp.h"

#if defined(__GNUC__)
#  define UNUSED __attribute__((__unused__))
#endif

static int fold_case = 0, verbose = 0, reverse = 0;

static void trace_result(char const *a, char const *b, int ret)
{
     char const *op;

     if (ret < 0)
	  op = "<";
     else if (ret > 0)
	  op = ">";
     else
	  op = "==";
     
     fprintf(stderr, "\tstrncatcmp: \"%s\" %s \"%s\"\n",
	     a, op, b);
}



static int compare_strings(const void *a, const void *b)
{
     char const *pa = *(char const **)a, *pb = *(char const **)b;
     int ret;

     if (fold_case)
	  ret = strnatcasecmp(pa, pb);
     else
	  ret = strnatcmp(pa, pb);

	 if (reverse)
	  ret *= -1;

	 if (verbose)
	  trace_result(pa, pb, ret);

     return ret;
}

int main(int argc, char **argv)
{
	int n; scanf("%d", &n);
	char **ar = (char **)malloc(sizeof(char *));
	for ( int i=0; i<n; ++i ) {
		ar[i] = (char *)malloc(105*sizeof(char));
		scanf("%s", ar[i]);
	}
	for ( int i=0; i<n; ++i ) {
		printf("%d: %s\n", i, ar[i]);
	}
	qsort(ar, n, sizeof(ar[0]), compare_strings);
	for ( int i=0; i<n; ++i ) {
		printf("%d:", i);
		puts(ar[i]);
	}	
	return 0;
}