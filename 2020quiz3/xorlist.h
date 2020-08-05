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