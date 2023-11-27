#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    if (head == NULL) {
    	return 0;
	}
    node* tortoise = head;
    node* hare = head->next;
    while(tortoise != hare) {
    	if (hare == NULL || hare->next == NULL) {
    		return 0;
		} else {
			tortoise = tortoise->next;
			hare = hare->next->next;
		}
	}
    return 1;
}
