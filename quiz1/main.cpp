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
        return start;
    }
    func_call++;
    list *left = start;
    list *right = left->next;
    
    int M = (L+R)/2;
    for ( int i=L; i<M-1; ++i ) {
        right = right->next;
    }

    list *left_end = right->prev;
    list *right_end = left->prev;

    left->prev = left_end;
    left_end->next = left;

    right->prev = right_end;
    right_end->next = right;

    left = sort(left, L, M);
    right = sort(right, M, R);
    int cnt = 0, l_cnt = 0, r_cnt = 0;
    list *merge = NULL;
    for (list *ll=left, *rr=right; cnt<R-L; ++cnt) {
        ++iteration;
        if ( r_cnt==R-M || (l_cnt!=M-L && ll->data < rr->data)) {
            if (!merge) {
                start = merge = ll; // LL1;
            } else {
                merge->next = ll; // LL2;
                merge->next->prev = merge;
                merge = merge->next;
            }
            ll = ll->next; // LL3;
            ++l_cnt;
        } else {
            if (!merge) {
                start = merge = rr; // LL4;
            } else {
                merge->next = rr; // LL5;
                merge->next->prev = merge;
                merge = merge->next;
            }
            rr = rr->next; // LL6;
            ++r_cnt;
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