#include <stdio.h>
#include <stdlib.h>

typedef struct __list {
    int data;
    struct __list *next;
} list;

int func_call = 0;
int iteration = 0;
list *sort(list *start) {
    if (!start || !start->next) {
        return start;
    }
    func_call++;
    list *left = start;
    list *right = left->next;

    left->next = NULL; // LL0;

    left = sort(left);
    right = sort(right);
    
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
    //printf("END start %d\n", start->data);
    return start;
}
void display (list *start) {
	for ( list *now=start; now; now=now->next ) {
		printf("%d ", now->data);
	} 
	printf("\n");
}
list *input () {
	int n; 
	scanf("%d", &n);
	if ( n == 0 ) {
		return (0);
	}
	list *start = (list*) malloc(sizeof(list));
	scanf("%d", &start->data);
	start->next = NULL;
	n--;
	
	for ( list *prev=start; n; n-- ) {
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
	list *start = input();
	display(start);
	start = sort(start);
	printf("func_call: %d\n", func_call);
	printf("iteration: %d\n", iteration);
	display(start);

	return 0;
}