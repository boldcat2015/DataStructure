/**
 * Requirements:
 * Given a singly linked list, determine if it is a palindrome.
 * 
 * We define a list to be palindrome if and only if the linked 
 * list has node vals in the same order wether you read from the head or the tail.
 * e.g. 1->2->3->2->1
 * 
 * BONUS for solutions using O(1) space!!!
**/

struct ListNode {
    int val;
    struct ListNode *next;
};

bool isPalindrome(struct ListNode* head) {
/* Your code should start here. */
    /* step 1: mark the middle of link */
    int n = 0;
    struct ListNode *head2, *p, *t;
    for (p = t = head; p ; p = p -> next) {
        n++;
        if (n % 2 && n > 1) {
            t = t -> next;
        }
    }
    head2 = (struct ListNode *)malloc(sizeof(struct ListNode));
    head2 -> next = t -> next; // here starts second half
    t -> next = NULL; // terminate first half link
    /* step 2: reverse the second half link */
    p = head2 -> next; // this part is identical to "reverseList.h"
    head2 -> next = NULL; // start from an empty link
    while (p) {
        t = p -> next;
        p -> next = head2 -> next;
        head2 -> next = p;
        p = t;
    }
    /* step 3: collate the first half with the second half */
    for (t = head -> next, p = head2 -> next; t ; p = p -> next, t = t -> next) {
        if (p -> val != t -> val) {
            return false;
        }
    }
    // note that mid-point of odd-length palindrome is at the end of second half,
    // so length of first half is less than or equal to that of the second,
    // which explain why 't' is used to judge the condition of for-loop.
    return true;
/* End of your code. */
}
