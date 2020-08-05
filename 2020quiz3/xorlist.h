// XOR Linked-List
#include <stdint.h>
#include <stdlib.h>

typedef struct __list list;
struct __list {
    int data;
    struct __list *addr; // link = addr_prev XOR addr_next
};

#define XOR(a, b) ((list *) ((uintptr_t) (a) ^ (uintptr_t) (b)))

void insert_node(list **l, int d) {
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
