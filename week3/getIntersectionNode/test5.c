#include"getIntersectionNode.c"

void creatIntersectionLnkLst(struct ListNode **, struct ListNode **, int*, int*, int*);
void printInsertLnkLst(struct ListNode *, struct ListNode *, int, int, int);
void printLst(struct ListNode *);

int main(int argc, char** argv){
    int i;
    struct ListNode *headA = NULL, *headB = NULL, *headC = NULL;
    int lenA = 0, lenB = 0, lenC = 0, lenD = 0;
    srand(time(NULL));
    /* Initialize and print the linked lists. */
    creatIntersectionLnkLst(&headA, &headB, &lenA, &lenB, &lenC);
    printf("The original list:\n\n");
    printInsertLnkLst(headA, headB, lenA, lenB, lenC);
    /* Test on a single group of lists. */
    headC = getIntersectionNode(headA, headB);
    printf("The intersection of the lists:\n\t");
    printLst(headC);
    for (lenD = 0; headC; lenD++, headC = headC->next);
    if (lenD != lenC)
        printf("Incorrect answer.\n");
    else{
        /* Test on multiple groups of lists. */
        printf("Correct answer.\n\nStart testing with %d random cases...\n\n",NUMCASE);
        for (i = 0; i < NUMCASE; i++){
            headA = NULL, headB = NULL, headC = NULL;
            lenA = 0, lenB = 0, lenC = 0, lenD = 0;
            creatIntersectionLnkLst(&headA, &headB, &lenA, &lenB, &lenC);
            headC = getIntersectionNode(headA, headB);
            for (lenD = 0; headC; lenD++, headC = headC->next);
            if (lenD != lenC)
                break;
        }if (i == NUMCASE)
            printf("Your code runs well!\n");
        else{
            /* Print input that causes error. */
            printf("Incorrect answer.\n");
            printf("The original list:\n\n");
            printInsertLnkLst(headA, headB, lenA, lenB, lenC);
            printf("The intersection of the lists:\n\t");
            printLst(getIntersectionNode(headA, headB));
        }
    }
    return 0;
}

/* Initialize and the linked lists. */
void creatIntersectionLnkLst(struct ListNode **headA, struct ListNode **headB, int* lenA, int* lenB, int* lenC){
    int i;
    struct ListNode *probeA, *probeB;
    *lenA = rand() % 6;
    *lenB = rand() % 6;
    *lenC = rand() % 6;
    if (*lenA){
    /* If applicable, initialized the independent part of list A. */
        *headA = (struct ListNode *)malloc(sizeof(struct ListNode));
        probeA = *headA;
        probeA->val = rand() % 100;
        probeA->next = NULL;
        for (i = 1; i < *lenA;i++)
        {
            probeA->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            probeA = probeA->next;
            probeA->val = rand() % 100;
            probeA->next = NULL;
        }
    } if (*lenB){
    /* If applicable, initialized the independent part of list B. */
        *headB = (struct ListNode *)malloc(sizeof(struct ListNode));
        probeB = *headB;
        probeB->val = rand() % 100;
        probeB->next = NULL;
        for (i = 1; i < *lenB;i++)
        {
            probeB->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            probeB = probeB->next;
            probeB->val = rand() % 100;
            probeB->next = NULL;
        }
    } if (*lenC){
    /* Initialized the intersection part. */
        if (!*lenA && !*lenB){
            *headA = (struct ListNode *)malloc(sizeof(struct ListNode));
            probeA = *headA, *headB = probeA, probeB = probeA;
        }else if (!*lenA){
            probeB->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            probeB = probeB->next, *headA = probeB, probeA = probeB;
        }else{
            probeA->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            probeA->val = rand() % 100;
            probeA = probeA->next;
            if (!*lenB)
                *headB = probeA;
            else
                probeB->next = probeA;
        }
        probeA->val = rand() % 100;
        probeA->next = NULL;
        for (i = 1; i < *lenC; i++){
            probeA->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            probeA = probeA->next;
            probeA->val = rand() % 100;
            probeA->next = NULL;
        }
    }
}

/* Print and the linked lists. */
void printInsertLnkLst(struct ListNode *headA, struct ListNode *headB, int lenA, int lenB, int lenC){
    int m = lenA - lenB;
    int sp = lenA >= lenB? lenA: lenB;
    int i;
    /* Print the independent part of list A. */
    printf("List A:\t");
    if (m < 0)
        printf("%*c",4*(-m),' ');
    for (i = 0; i < lenA; i++,headA = headA->next)
        printf("%2d->",headA->val);
    printf("\b\b  \n");
    /* Print the intersection part. */
    printf("%*c> ", 4*sp+6, ' ');
    for (i = 0; i < lenC; i++,headA = headA->next)
        printf("%2d->",headA->val);
    printf("\b\b  \n");
    /* Print the independent part of list B. */
    printf("List B:\t");
    if (m > 0)
        printf("%*c",4*(m),' ');
    for (i = 0; i < lenB; i++,headB = headB->next)
        printf("%2d->",headB->val);
    printf("\b\b  \n\n");
}

/* Initialize and a linked list. */
void printLst(struct ListNode * probe){
    if (probe == NULL)
        printf("null\n");
    else{
        for (; probe != NULL; probe = probe->next){
            printf("%d->",probe->val);
        }
        printf("\b\b  \n");
    }
}

/** Zhang Chen, Dept. EE, Fudan University, 2016 **/