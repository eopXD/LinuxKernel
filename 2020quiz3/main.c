#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "xorlist.h"

int func_call = 0;
int iteration = 0;
list *sort ( list *start, int L, int R )
{
    func_call++;
    if ( R <= L+1 )
        return start;
    int M = (L + R) / 2;
    list *left = start, *right, *left_end;

    left_end = travel(left, NULL, M - L - 1);
    right = travel(left, NULL, M - L);

    left_end->addr = XOR(left_end->addr, right);
    right->addr = XOR(right->addr, left_end);

    left = sort(left, L, M);
    right = sort(right, M, R);

    for (list *merge = NULL; left || right;) {
        iteration++;
        if (!right || (left && left->data < right->data)) {
            list *next = left->addr;
            if (next)
                next->addr = XOR(left, next->addr);

            if (!merge) {
                start = merge = left;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(merge->addr, left);
                left->addr = merge;
                merge = left;
            }
            left = next;
        } else {
            list *next = right->addr;
            if (next)
                next->addr = XOR(right, next->addr);

            if (!merge) {
                start = merge = right;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(merge->addr, right);
                right->addr = merge;
                merge = right;
            }
            right = next;
        }
    }

    return start;
}
void certify ( list *start ) {
    list *now = start, *prev = NULL, *next;
    while ( now ) {
        if ( prev ) {
            assert(prev->data <= now->data);
        }
        next = XOR(now->addr, prev);
        prev = now;
        now = next;
    }
    puts("certified!!!");
}
int main ()
{

	list *head = NULL;
    int n = 10000;
    srand(time(NULL));
    for ( int i=0; i<n; ++i )  {
        insert_head(&head, rand());
    }
    
    head = sort(head, 0, n);
    
    certify(head);
    printf("func_call: %d\n", func_call);
    printf("iteration: %d\n", iteration);
	
	return 0;
}