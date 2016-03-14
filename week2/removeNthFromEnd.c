/**
 * Requiments:
 * 1. Given a linked list, remove the nth node from the end of list
 *    and return its head.
 * 2. Think about the time complexity and space complexity
 *    of you function and write it in your report.
 * 
 * For example:
 * Given linked list: 1->2->3->4->5, and n = 2.
 * After removing the second node from the end,
 * the linked list becomes 1->2->3->5.
 * 
 * Note:
 * You may assume that the given n will always be valid.
**/

#include<stdio.h>
#include<stdlib.h>
#include <time.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
/* Your code should start from here. */
    struct ListNode* p = head;
    int len = 1, i;
    while (p -> next) { // get the length of link
        len++;
        p = p -> next;
    }
    if (len == n) { // head is moved
        return head -> next;
    }
    for (i = 0, p = head; i < len; i++, p = p -> next) {
        if (i == len - n - 1) {
            p -> next = p -> next -> next;
            break;
        }
    }
    return head;
/* End of your code. */
}

/* Warning: Testbench. PLEASE leave it INTACT. */
/* Warning: Testbench. PLEASE leave it INTACT. */
/* Warning: Testbench. PLEASE leave it INTACT. */

void printLst(struct ListNode *);
void deleteLst(struct ListNode *);

int main(int argc, char** argv){
    struct ListNode *head, *probe;
    int lstSize[5] = {1,2,4,8,16};
    int Loc[5];
    int i;
    srand(time(NULL));
    for (i = 0; i < 5; i++)
        Loc[i] = rand() % lstSize[i] + 1;
    for (i = 0; i < 5; i++){
        int j;
        /* Initialize the linked list. */
        head = NULL;
        if (lstSize[i]){
            head = (struct ListNode *)malloc(sizeof(struct ListNode));
            head->val = rand() % 100;
            head->next = NULL;
        }
        for (probe = head, j = 1; j < lstSize[i]; j++){
            probe->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            probe = probe->next;
            probe->val = rand() % 100;
            probe->next = NULL;
        }
        printf("Case%2d: remove #%d element from the end of \n",i+1,Loc[i]);
        printLst(head);
        /* Test */
        printf("The new linked list is:\n");
        printLst(removeNthFromEnd(head, Loc[i]));
        printf("\n");
        deleteLst(head);
    }
    return 0;
}

/* Print the linked list. */
void printLst(struct ListNode * probe){
    for (; probe != NULL; probe = probe->next){
        printf("%d->",probe->val);
    }
    printf("\b\b  \n");
}

/* Delete the linked list. */
void deleteLst(struct ListNode *head){
    if (head == NULL)
        return;
    deleteLst(head->next);
    free(head);
    return;
}

/** Zhang Chen, Dept. EE, Fudan University, 2016 **/
