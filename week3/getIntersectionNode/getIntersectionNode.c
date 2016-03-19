/**
 * Write a program to find the node at which 
 * the intersection of two singly linked lists begins.
 * 
 * 
 * For example, the following two linked lists:
 * 
 * A:          a1 → a2
 *                    ↘
 *                      c1 → c2 → c3
 *                   ↗            
 * B:     b1 → b2 → b3
 * begin to intersect at node c1.
 * 
 * 
 * Notes:
 * 1. If the two linked lists have no intersection at all, return null.
 * 2. The linked lists must retain their original structure after the function returns.
 * 3. You may assume there are no cycles anywhere in the entire linked structure.
 * 4. Your code should preferably run in O(n) time and use only O(1) memory.
**/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUMCASE 10000

/* Definition for singly-linked list.*/
struct ListNode {
    int val;
    struct ListNode *next;
};
 
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
/* Your code should start from here. */
    int LenA = 0, LenB = 0, d, i;
    struct ListNode *p, *q;
    for (p = headA; p ; p = p -> next) { // first compute length of each link
        LenA ++;
    }
    for (p = headB; p ; p = p -> next) {
        LenB ++;
    }
    if (LenA > LenB) { // start comparing from the shorter one
        p = headB;
        q = headA;
        d = LenA - LenB;
    }
    else {
        p = headA;
        q = headB;
        d = LenB - LenA;
    }
    for (i = 0; i < d; i++) { // synchronize q on longer link with p on shorter link
        q = q -> next;
    }
    for (; p ; p = p -> next, q = q -> next) {
        if (p == q) { // first matched pair
            return p; // and so intersection starts from here
        }
    }
    return NULL;
/* End of your code. */
}
