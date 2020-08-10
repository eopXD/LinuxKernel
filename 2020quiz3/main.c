#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "xorlist.h"

int func_call = 0;
int iteration = 0;

int main ()
{
    list *head = NULL;
    int n = 10000000;
    int *origin = malloc(sizeof(int) * n);
    srand(time(NULL));
    for ( int i=0; i<n; ++i )  {
        origin[i] = rand();
    }
    for ( ; S < MAX_S; S*=2 ) {
        func_call = 0;
        iteration = 0;    
        list *head = NULL;
        for ( int i=0; i<n; ++i ) {
            insert_head(&head, origin[i]);
        }
        
        clock_t t1, t2;
        t1 = clock();
        head = merge_sort(head, 0, n);
        t2 = clock();

        certify(head);
        printf("N %d S %d func_call %d iteration %d %lf\n", n, S, func_call, iteration, (t2-t1) / (double)CLOCKS_PER_SEC);
        
        delete_list(head);
    }

    
	return 0;
}