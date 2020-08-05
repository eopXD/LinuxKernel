#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "xorlist.h"

int func_call = 0;
int iteration = 0;
list *sort(list *start)
{
    func_call++;
    if (!start || !start->addr)
        return start;

    list *left = start, *right = start->addr;
    left->addr = NULL;
    right->addr = XOR(right->addr, left);

    left = sort(left);
    right = sort(right);

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
int main ()
{

	list *head = NULL;
    int n = 10000;
    srand(time(NULL));
    int ar[n];
    for ( int i=0; i<n; ++i )  {
        insert_head(&head, rand());

    }
	//print_list(head);
    head = sort(head);
    printf("func_call: %d\n", func_call);
    printf("iteration: %d\n", iteration);
	//print_list(head);

	return 0;
}