#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "xorlist.h"

#define MAX_S 4096
int func_call = 0;
int iteration = 0;

int S = 10;
int ar[MAX_S];

void swap ( list *a, list *b ) {
    int tmp = a->data;
    a->data = b->data;
    b->data = tmp;
}
list* bubble_sort ( list *start, int len ) {
    list *now, *prev = NULL, *next;
    list *inner_now, *inner_prev, *inner_next;
    now = start;
    for ( int i=0; i<len; ++i ) {
        inner_now = now;
        inner_prev = prev;
        for ( int j=0; j<len-i-1; ++j ) {
            inner_next = XOR(inner_now->addr, inner_prev);
            if ( inner_now->data > inner_next->data ) {
                swap(inner_now, inner_next);
            }
            inner_prev = inner_now;
            inner_now = inner_next;
        }
    }
    return start;
}
list* insertion_sort ( list *start, int len ) {
    list *now, *prev = NULL, *next;
    list *inner_now, *inner_prev = NULL, *inner_next;
    now = start;
    for ( int i=1; i<len; ++i ) {
        next = XOR(now->addr, prev);
        inner_now = now;
        inner_prev = next;
        int j = i - 1;
        while ( j >= 0 && inner_prev->data < inner_now->data ) {
            swap(inner_now, inner_prev);
            inner_next = XOR(inner_now->addr, inner_prev);
            inner_prev = inner_now;
            inner_now = inner_next;
            j--;
        }
        prev = now;
        now = next;
    }
    return start;
}

list* merge_sort ( list *start, int L, int R )
{    
    func_call++;
    if ( R - L <=  S ) {
        //start = insertion_sort(start, R - L);
        start = bubble_sort(start, R - L);
        return start;
    }
    int M = (L + R) / 2;
    list *left = start, *right, *left_end;

    left_end = travel(left, NULL, M - L - 1);
    right = travel(left, NULL, M - L);

    left_end->addr = XOR(left_end->addr, right);
    right->addr = XOR(right->addr, left_end);

    left = merge_sort(left, L, M);
    right = merge_sort(right, M, R);

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
//    puts("certified!!!");
}
int main ()
{
    list *head = NULL;
    int n = 50;
    for ( int i=0; i<n; ++i ) {
        insert_head(&head, rand()%100);
    }
    head = merge_sort(head, 0, n);
    certify(head);
    delete_list(head);
    return (0);

	int *origin = malloc(sizeof(int) * n);
    srand(time(NULL));
    for ( int i=0; i<n; ++i )  {
        origin[i] = rand();
    }
    for ( ; S < MAX_S; ++S ) {
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