#include <stdio.h>

#include "xorlist.h"

list *sort(list *start)
{
    if (!start || !start->addr)
        return start;

    list *left = start, *right = start->addr;
    left->addr = NULL;
    right->addr = XOR(right->addr, left);

    left = sort(left);
    right = sort(right);

    for (list *merge = NULL; left || right;) {
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
	insert_head(&head, 1);
	insert_head(&head, 1);
	insert_head(&head, 2);
	insert_head(&head, 3);
	insert_head(&head, 5);
	insert_head(&head, 8);
	insert_head(&head, 13);
	
	print_list(head);
	
	head = sort(head);

	print_list(head);

	return 0;
}