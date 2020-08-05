#include <stdio.h>

#include "xorlist.h"

int main ()
{

	list *head = NULL;
	insert_head(&head, 13);
	insert_head(&head, 8);
	insert_head(&head, 5);
	insert_head(&head, 2);
	insert_head(&head, 3);
	insert_head(&head, 1);
	insert_head(&head, 1);
	
	print_list(head);
	print_list(head);

	return 0;
}