// XOR Linked-List
// main drawback: unable to delete element inside list
#include <stdint.h>
#include <stdlib.h>

typedef struct __list list;
struct __list {
    int data;
    struct __list *addr; // link = addr_self XOR addr_next
};

#define XOR(a, b) ((list *) ((uintptr_t) (a) ^ (uintptr_t) (b)))

void insert_head(list **l, int d) { // insert to head
    list *tmp = malloc(sizeof(list));
    tmp->data = d;

    if (!(*l)) {
        tmp->addr = NULL;
    } else {
        (*l)->addr = XOR(tmp, (*l)->addr);
        tmp->addr = *l;
    }
    *l = tmp;
}

void delete_list(list *l) {
    while (l) {
        list *next = l->addr;
        if (next)
            next->addr = XOR(next->addr, l); // link = addr_prev XOR addr_next
        free(l);
        l = next;
    }
}

void print_list ( list *l ) {
    list *now = l, *prev = NULL, *next;

    while ( now ) {
        printf("%d ", now->data);
        
        next = XOR(prev, now->addr);
        prev = now;
        now = next;
    }
    puts("");
}
// return the x-th element with *l as the head, 0-th = *l
list* travel ( list *now, list *prev, int x ) {
    list *next;
    while ( x > 0 && now  ) {
        next = XOR(prev, now->addr);
        prev = now;
        now = next;
        x--;
    }
    return now;
}
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
        start = insertion_sort(start, R - L);
        //start = bubble_sort(start, R - L);
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
