/**
 * Requirement:
 * Reverse a singly linked list
 * and return the head of the reversed list. 
**/
#include <test11.c>
struct ListNode {
    int val;
    struct ListNode *next;
};

void reverseList(struct ListNode* head) {
/* Your code should start from here. */
/* Note that from this time on, struct ListNode* head is default to be a meaningless struct
   which is the predecessing node of the list of nodes of some meaning. */
    struct ListNode* p = head -> next;
    struct ListNode* t;
    head -> next = NULL;
    while (p) {
        t = p -> next;
        p -> next = head -> next;
        head -> next = p;
        p = t;
    }
/* End of your code. */
}
