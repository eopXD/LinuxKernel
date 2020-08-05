// XOR Linked-List
// main drawback: unable to delete element inside list
#include <stdint.h>
#include <stdlib.h>

typedef struct __list list;
struct __list {
    int data;
    struct __list *addr; // link = addr_self XOR addr_next
};


/*


NULL A NULL

insert B, given ADDR_A, so we also have ADDR_B
ADDR_B = ADDR_A
ADDR_A = ADDR_B XOR ADDR_A 


*/

#define XOR(a, b) ((list *) ((uintptr_t) (a) ^ (uintptr_t) (b)))

#define prev(a) ((list *) ((uintptr_t) ))

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