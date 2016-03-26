#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"reverseList.h"

void printLst(struct ListNode *);
void deleteLst(struct ListNode *);

int main(int argc, char** argv){
    struct ListNode *head, *probe;
    int lstSize[4] = {0,1,2,8};
    int i;
    srand(time(NULL));
    for (i = 0; i < 4; i++){
        int j;
        /* Initialize the linked list. */
        head = NULL;
        head = (struct ListNode *)malloc(sizeof(struct ListNode));
        head->val = 0x7a636664;
        head->next = NULL;
        for (probe = head, j = 0; j < lstSize[i]; j++){
            probe->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            probe = probe->next;
            probe->val = rand() % 100;
            probe->next = NULL;
        }
        printf("Case%2d: \n",i+1);
        printf("The original linked list:\n");
        printLst(head);
        /* Test */
        printf("The reversed linked list:\n");
        reverseList(head);
        printLst(head);
        printf("\n");
        deleteLst(head);
    }
	system("pause");
    return 0;
}

/* Print the linked list. */
void printLst(struct ListNode * head){
    struct ListNode *probe = head->next;
    if( probe == NULL)
        printf("null\n");
    else{
        for (; probe != NULL; probe = probe->next){
            printf("%d->",probe->val);
        }
        printf("\b\b  \n");
    }
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