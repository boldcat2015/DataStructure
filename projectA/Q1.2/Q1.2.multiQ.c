/* This file solves Question 2 in Project A,
 * in course Data Structure, 2016 spring.
 *
 * Tasks:
 * Maintain a priority structure of patients which supports 4 function:
 * 1. enqueue
 * 2. dequeue
 * 3. update / switch queue
 * 4. remove
 * using the method of multiple queue using linked list
 *
 * May 2016, Cheng Yuge, Fudan University
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 1048576
#define NAMESIZE 200
#define IDSCALE 1000003
FILE *FIN, *FOUT;

typedef struct Patient {
    char name[NAMESIZE];
    int ID;
    int level; // of emergency
    struct Patient *next;
    struct Patient *prev;
    int isHead;
    struct Head *head;
} Patient;

typedef struct Head { // link the linked lists together, in descending sequence of level.
    Patient *head;
    struct Head *next;
    struct Head *prev;
} Head;

Head *root; // head of heads of queues
Patient *findPatient[IDSCALE]; // find patient by ID

void init ();
void goLowerCase (char*);
int myAtoi (char*); // string to integer
int isLetterDigit (char c);
void enQ (char*, int, int, int);
void deQ ();
void quitQ (int, int);
void update (int, int);
void printQ ();
void mainLoop ();

int main () {
    init ();
    mainLoop ();
    printf("closing files.\n");
    fclose (FIN);
    fclose (FOUT);
    printf("exiting.\n");
    return 0;
}

void init () { // open file
    FIN = fopen("./input2.txt", "r");
    FOUT = fopen("./output2.txt", "w+");
    if ( !FIN ) {
        printf("\e[31mFailed to open input1.txt.\e[0m\n");
        exit(1);
    }
    printf("\e[32msuccessfully opened input2.txt\e[0m.\n");
    root = (Head*)malloc(sizeof(Head));
    root -> head = NULL;
    root -> next = NULL;
    root -> prev = NULL;
    int i;
    for (i = 0; i < IDSCALE; i++) {
        findPatient[i] = NULL;
    }
    printf("\e[32msuccessfully initialized.\e[0m\n");
}

void goLowerCase (char *w) {
    int i;
    for (i = 0; i < strlen(w); i++) {
        if (w[i] >= 'A' && w[i] <= 'Z') {
            w[i] = w[i] - 'A' + 'a';
        }
    }
}

int myAtoi(char* str){
    if (!str) {
        return 0 ;
    }
    int ans = 0 , n = strlen( str ), i, sign = 0 , start = -1 ;
    char c;
    /* first discard prefix whitespaces */
    for (i = 0, c = str[i]; i < n && (c == ' ' || c == '\t' || c == '\n'); i++, c = str[i]);
    for ( ; i < n; i++) {
        c = str[i];
        if (start == -1) { /* deal with the optional sign symbol */
            if (c == '+') {
                sign = 1 ;
                start = i ;
            }
            else if (c == '-') {
                sign = -1 ;
                start = i ;
            }
            else if ((int)c >= (int)('0') && (int)c <= (int)('9')) {
                start = i ;
                ans = (int)c - (int)('0');
            }
            else {
                return 0 ;
            }
        }
        else if ((int)c >= (int)('0') && (int)c <= (int)('9')) {
            /* check if out of bounce */
            if (sign == -1 && ((ans == 214748364 && (int)c > 7 )|| ans > 214748364) ) {
                return 0x80000000 ;
            }
            else if ((ans == 214748364 && (int)c > 6 )|| ans > 214748364) {
                return 0x7fffffff ;
            }
            /* update ans */
            ans *= 10 ;
            ans += (int)c - (int)('0') ;
        }
        else {
            break ;
        }
    }
    if (sign == -1) {
        ans *= -1 ;
    }
    return ans ;
}

int isLetterDigit (char c) {
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return 1;
    }
    return 0;
}

void enQ (char *name, int id, int lvl, int verbose) {
    Patient *p = (Patient*)malloc(sizeof(Patient)), *tmp;
    findPatient[id % IDSCALE] = p;
    strcpy (p -> name, name);
    p -> ID = id;
    p -> level = lvl;
    p -> next = NULL;
    p -> prev = NULL;
    p -> isHead = 0;
    p -> head = NULL;
    if (verbose == 1) {
        printf("\e[35m%s\e[0m, \e[35m%d\e[0m, lvl.\e[35m%d\e[0m", name, id, lvl);
    }
    Head *h = root, *tmph;
    while (h -> next && h -> next -> head -> level > lvl) { // go pass higher lvl patients' Qs
        h = h -> next;
    }
    if (!(h -> next) || h -> next -> head -> level < lvl) { // new level
        tmph = h -> next;
        h -> next = (Head*)malloc(sizeof(Head));
        h -> next -> next = tmph;
        h -> next -> prev = h;
        h -> next -> head = p;
        p -> isHead = 1;
        p -> head = h -> next;
        if (tmph) {
            tmph -> prev = h -> next;
        }
        if (verbose == 1) {
            printf(" comes as first of his level.\n");
        }
        return ;
    }
    else if (h -> next -> head -> level == lvl) { // queue at tail of this level
        tmp = h -> next -> head;
        while (tmp -> next) { // go to tail
            tmp = tmp -> next;
        }
        tmp -> next = p;
        p -> prev = tmp;
        if (verbose == 1) {
            printf(" comes to queue.\n");
        }
    }
}

void deQ () {
    if (!(root -> next)) {
        printf("No patients in the waiting line.\n");
        return ;
    }
    Patient *p = root -> next -> head;
    Head *tmph;
    printf("\e[35m%s\e[0m, \e[35m%d\e[0m, lvl.\e[35m%d\e[0m goes to the doctor", p -> name, p -> ID, p -> level);
    fprintf(FOUT, "%s, %d\n", p -> name, p -> ID);
    if (!(p -> next)) { // level cleared
        tmph = root -> next;
        root -> next = root -> next -> next;
        if (root -> next) {
            root -> next -> prev = root;
            printf(", no more lvl.%d patients", p -> level);
        }
        else {
            printf(", no more patients are waiting");
        }
        free(tmph);
    }
    else {
        if (p -> isHead == 1) {
            p -> next -> isHead = 1;
            p -> next -> prev = NULL;
            p -> next -> head = p -> head;
            p -> head -> head = p -> next;
        }
        else {
            p -> prev -> next = p -> next;
            p -> next -> prev = p -> prev;
        }
    }
    printf(".\n");
    findPatient[(p -> ID) % IDSCALE] = NULL;
    free(p);
}

void quitQ (int id, int verbose) {
    if (!findPatient[id % IDSCALE]) {
        printf("No patient found by ID %d.\n", id);
        return ;
    }
    Patient *p = findPatient[id % IDSCALE];
    if (verbose == 1) {
        printf("\e[35m%s\e[0m, \e[35m%d\e[0m, lvl.\e[35m%d\e[0m quits the line", p -> name, p -> ID, p -> level);
    }
    Head *h;
    if (p -> isHead == 1) {
        if (p -> next) {
            p -> next -> isHead = 1;
            p -> next -> prev = NULL;
            p -> next -> head = p -> head;
            p -> head -> head = p -> next;
        }
        else { // level cleared
            h = p -> head;
            h -> prev -> next = h -> next;
            if (h -> next) {
                h -> next -> prev = h -> prev;
            }
            else if (verbose == 1) {
                if (h -> prev == root) { // all cleared
                    printf(", no more patients are waiting");
                }
                else {
                    printf(", no more lvl.%d patients", p -> level);
                }
            }
            free(h);
        }
    }
    else {
        p -> prev -> next = p -> next;
        if (p -> next) {
            p -> next -> prev = p -> prev;
        }
    }
    if (verbose == 1) {
        printf(".\n");
    }
    findPatient[(p -> ID) % IDSCALE] = NULL;
    free(p);
}

void update (int id, int lvl) {
    if (!findPatient[id % IDSCALE]) {
        printf("No patient found by ID %d.\n", id);
        return ;
    }
    Patient *p = findPatient[id % IDSCALE];
    printf("\e[35m%s\e[0m, \e[35m%d\e[0m, lvl.%d -> lvl.\e[35m%d\e[0m updated.\n", p -> name, p -> ID, p -> level, lvl);
    char name[NAMESIZE];
    strcpy (name, p -> name);
    quitQ (id, 0);
    enQ (name, id, lvl, 0);
}

void printQ () {
    Head *h = root -> next;
    printf("\e[36m╔════════════════════════════════════════\e[0m\n");
    if (!h) {
        printf("No patients in the waiting line.\n");
    }
    else {
        Patient *p;
        int i = 0;
        printf("\e[36m║\e[0mWaiting list (with descending priority):\n");
        while (h) {
            p = h -> head;
            while (p) {
                i++;
                printf("\e[36m║\e[0m   %d. %s, %d, lvl.%d\n", i, p -> name, p -> ID, p -> level);
                p = p -> next;
            }
            h = h -> next;
        }
    }
    printf("\e[36m╚════════════════════════════════════════\e[0m\n");
}

void mainLoop () {
    char buff[BUFFSIZE];
    int i, s, a, l = 0;
    char args[4][NAMESIZE]; // operation, arg1, arg2, arg3.
    while (fgets (buff, BUFFSIZE, FIN)) {
        l++;
        a = 0; // argument #
        // printf("\nline %d: buff = %s", l, buff);
        for (i = 0, s = -1; buff[i]; i++) { // get all arguments in this line
            if (s == -1 && isLetterDigit(buff[i]) == 1)  { // a new word starts here.
                s = i;
            }
            if (s != -1 && isLetterDigit(buff[i]) == 0) { // word ends here.
                if (a > 3) {
                    printf("\e[31mError:\e[0m Too many arguments on line %d.\n", l);
                    exit(2);
                }
                strncpy (args[a], &buff[s], i - s);
                args[a][i - s] = '\0';
                // printf ("read in arg[%d] = '%s',\n", a, args[a]);
                s = -1;
                a++;
            }
        }
        goLowerCase (args[0]);
        printf("interpreting operation:");
        if (strcmp(args[0], "enqueue") == 0) {
            printf("[\e[32menqueue\e[0m].\n");
            enQ (args[1], myAtoi(args[2]), myAtoi(args[3]), 1);
        }
        else if (strcmp(args[0], "dequeue") == 0) {
            printf("[\e[32mdequeue\e[0m].\n");
            deQ ();
        }
        else if (strcmp(args[0], "update") == 0) { 
            printf("[\e[32mupdate\e[0m].\n");
            update (myAtoi(args[1]), myAtoi(args[2]));
        }
        else if (strcmp (args[0], "quit") == 0) {
            printf("[\e[32mquit\e[0m].\n");
            quitQ (myAtoi(args[1]), 1);
        }
        else if (strcmp(args[0], "print") == 0) {
            printf("[\e[32mprint\e[0m].\n");
            printQ ();
        }
    }
}

/* End of file */
