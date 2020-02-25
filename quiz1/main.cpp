#include <stdio.h>
#include <stdlib.h>

typedef struct __list {
    int data;
    struct __list *next;
    struct __list *prev;
} list;

int func_call = 0;
int iteration = 0;
list *sort(list *start, int L, int R) {
    if ( R <= L+1 ) {
    	start->next = start->prev = start;
        return start;
    }
    func_call++;
    list *left = start;
    list *right = left->next;
    
    int M = (L+R)/2;
    for ( int i=L; i<M-1; ++i ) {
        right = right->next;
    }

    left = sort(left, L, M);
    right = sort(right, M, R);
    
    left->prev->next = right->prev->next = NULL;
    
    list *merge = NULL;
    
    for ( ; left || right; ) {
    	++iteration;
        if ( !right || (left && left->data < right->data)) {
            if (!merge) {
                start = merge = left; // LL1;
            } else {
                merge->next = left; // LL2;
                merge->next->prev = merge;
                merge = merge->next;
            }
            left = left->next; // LL3;
        } else {
            if (!merge) {
                start = merge = right; // LL4;
            } else {
                merge->next = right; // LL5;
                merge->next->prev = merge;
                merge = merge->next;
            }
            right = right->next; // LL6;
        }
    }
    merge->next = start;
    start->prev = merge;
    return start;
}

void display (list *start) {
    for ( list *now=start; ; now=now->next ) {
        printf("%d, prev: %d, next: %d\n", now->data, now->prev->data, 
         now->next->data);
        if ( now->next == start ) {
        	break;
        }
    } 
    printf("\n");
}


list *input ( int &n ) {
    scanf("%d", &n);
    int tmp = n;
    if ( tmp == 0 ) {
        return (0);
    }
    list *start = (list*) malloc(sizeof(list));
    scanf("%d", &start->data);
    start->next = start->prev = NULL;
    tmp--;
    list *prev;
    for ( prev=start; tmp; tmp-- ) {
        list *elem = (list*) malloc(sizeof(list));
        scanf("%d", &elem->data);
        elem->next = NULL;
        elem->prev = prev;
        prev->next = elem;
        prev = elem;
    }
    prev->next = start;
    start->prev = prev;
    return start;
}
int main ()
{
    int n;
    list *start = input(n);
    printf("n: %d\n", n);
    display(start);
    start = sort(start, 0, n);
    printf("func_call: %d\n", func_call);
    printf("iteration: %d\n", iteration);
    display(start);

    return 0;
}