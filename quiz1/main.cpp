#include <stdio.h>
#include <stdlib.h>

typedef struct __list {
    int data;
    struct __list *next;
} list;

int func_call = 0;
int iteration = 0;
list *sort(list *start, int L, int R) {
    if ( R <= L+1 ) {
        return start;
    }
    func_call++;
    list *left = start;
    list *prev = left;
    list *right = prev->next;
    
    int M = (L+R)/2;
    for ( int i=L; i<M-1; ++i ) {
        prev = right;
        right = right->next;
    }

    prev->next = NULL; // LL0;

    left = sort(left, L, M);
    right = sort(right, M, R);
    
    for (list *merge = NULL; left || right; ) {
        ++iteration;    	
        if (!right || (left && left->data < right->data)) {
            if (!merge) {
                start = merge = left; // LL1;
            } else {
                merge->next = left; // LL2;
                merge = merge->next;
            }
            left = left->next; // LL3;
        } else {
            if (!merge) {
                start = merge = right; // LL4;
            } else {
                merge->next = right; // LL5;
                merge = merge->next;
            }
            right = right->next; // LL6;
        }
    }
    return start;
}
void display (list *start) {
    for ( list *now=start; now; now=now->next ) {
        printf("%d ", now->data);
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
    start->next = NULL;
    tmp--;

    for ( list *prev=start; tmp; tmp-- ) {
        list *elem = (list*) malloc(sizeof(list));
        elem->next = NULL;
        scanf("%d", &elem->data);
        prev->next = elem;
        prev = elem;
    }
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