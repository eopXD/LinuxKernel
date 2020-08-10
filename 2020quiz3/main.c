#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "xorlist.h"

#define MAX_S 4096
int func_call = 0;
int iteration = 0;

int S = 1;
int ar[MAX_S];
void swap ( int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
void swap ( list *a, list *b ) {
    list *pre_a, *pre_b;
    pre_a = XOR(a->addr, b);
    pre_b = XOR(b->addr, a);
    if ( pre_a != NULL ) {
        pre_a->addr = XOR(pre_a->addr, XOR(a, b));
    }
    if ( pre_b != NULL ) {
        pre_b->addr = XOR(pre_b->addr, XOR(a, b));
    }
    a->addr = XOR(b, pre_b);
    b->addr = XOR(a, pre_a);
}
void get_data ( list *start, int len ) {
    list *now = start;
    list *prev = NULL, *next;
    for ( int i=0; i<len; ++i ) {
        ar[i] = now->data;
        next = XOR(now->addr, prev);
        prev = now;
        now = next;
    }
}
void overwrite_data ( list *start, int len ) {
    list *now = start;
    list *prev = NULL, *next;
    for ( int i=0; i<len; ++i ) {
        now->data = ar[i];
        next = XOR(now->addr, prev);
        prev = now;
        now = next;
    }    
}

list* bubble_sort ( list *start, int len ) {
    get_data(start, len);
    for ( int i=0; i<len; ++i ) {
        for ( int j=i+1; j<len; ++j ) {

            if ( ar[i] > ar[j] ) 
                swap(&ar[i], &ar[j]);
        }
    }
    overwrite_data(start, len);
    return start;
}
list* insertion_sort ( list *start, int len ) {
    get_data(start, len);
    for ( int i=1; i<len; ++i ) {
        int j = i - 1;
        while ( j >= 0 && ar[j+1] < ar[j] ) {
            swap(&ar[j], &ar[j+1]);
            j--;
        }
    }
    overwrite_data(start, len);
    return start;
}

list* merge_sort ( list *start, int L, int R )
{    
    func_call++;
    if ( R - L <=  S ) {
        //bubble_sort(start, R - L);
        insertion_sort(start, R - L);
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
    int n = 1000000;
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