#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include"isPalindrome.h"

void creatLst(struct ListNode **,int *, int);
void printLst(struct ListNode *);
void deleteLst(struct ListNode *);
bool creatArray(int** ,int *);

int main(int argc, char** argv){
    struct ListNode* head;
    int *nums, numsSize;
    int i;
    bool flag;
    srand(time(NULL));
    flag = creatArray(&nums,&numsSize);
    creatLst(&head, nums, numsSize);
    printLst(head);
    if(flag != isPalindrome(head)){
        printf("Your judgement: %s\n",flag?"True":"False");
        printf("Incorrect...\n");
    }
    else{
        printf("Your judgement: %s\n",flag?"True":"False");
        printf("Correct!\n\nStart testing...\n\n");
        for (i = 0; i < 10000; i++){
            flag = creatArray(&nums,&numsSize);
            creatLst(&head, nums, numsSize);
            if(flag != isPalindrome(head)){
                printf("Error...\nLast input:\n");
                printLst(head);
                printf("Your judgement: %s\n",flag?"True":"False");
                break;
            }
        }printf("Your code runs well!\n\n");
    }
    system("pause");
    return 0;
}


/* Create the linked list based on an array. */
void creatLst(struct ListNode **head,int *nums, int numsSize){
    struct ListNode *probe;
    int i;
    (*head) = (struct ListNode *)malloc(sizeof(struct ListNode));
    probe = *head;
    probe->val = 0x7a636664;
    probe->next = NULL;
    for (i = 0;i < numsSize; i++){
        probe->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        probe = probe->next;
        probe->val = nums[i];
        probe->next = NULL;
    }
}

bool creatArray(int **nums,int* numsSize){
    int i, len, flag;
    flag = rand()%3;
    if (flag == 2){
        len = rand()%10*2;
        *nums = (int *)malloc(sizeof(int)*(len));
        for (i = 0; i < len/2; i++)
            (*nums)[i] = rand()%100;
        for (; i < len; i++)
            (*nums)[i] = (*nums)[len-1 - i];
    }else if (flag == 1){
        len = rand()%10*2+1;
        *nums = (int *)malloc(sizeof(int)*(len));
        for (i = 0; i < len/2; i++)
            (*nums)[i] = rand()%100;
        (*nums)[i] = rand()%100;
        for (i += 1; i < len; i++)
            (*nums)[i] = (*nums)[len-1 - i];
    }else{
        len = rand()%10+10;
        *nums = (int *)malloc(sizeof(int)*(len));
        for (i = 0; i < len; i++)
            (*nums)[i] = rand()%100;
    }*numsSize = len;
    return flag>0;
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
