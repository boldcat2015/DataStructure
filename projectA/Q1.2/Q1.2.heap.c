/* This file solves Question 2 in Project A,
 * in course Data Structure, 2016 spring.
 *
 * Tasks:
 * Maintain a priority structure of patients which supports 4 function:
 * 1. enqueue
 * 2. dequeue
 * 3. update / switch queue
 * 4. remove
 * using the method of heap
 *
 * May 2016, Cheng Yuge, Fudan University
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 1048576
#define NAMESIZE 200
#define IDSCALE 1000003
#define HEAPSIZE 1048576
FILE *FIN, *FOUT;
int N[2] = {0}; // total number of patients
int T = 0; // time stamp to distinguish patients on same level

typedef struct Patient {
    char name[NAMESIZE];
    int ID;
    int level; // of emergency
    int time;
} Patient;

Patient *H[2][HEAPSIZE]; // HEAP, 1 = original heap, 0 = heap for printing
int findPatient[IDSCALE] = {0}; // find patient position in heap by ID

void init ();
void goLowerCase (char*);
int myAtoi (char*); // string to integer
int isLetterDigit (char c);
void swapPatient (int, int, int); // swap a & b in heap h
int whoRules (Patient*, Patient*); // compare priority
void enQ (char*, int, int, int); // if verbose == 0, this is used for update
void rollDown (int, int); // remove t, then roll down last patient from here. in heap h.
Patient *deQ (int); // if noprint == 0, that means this deQ is used for printing
void quitQ (int, int); // if verbose == 0, this is used for update
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
    int i;
    for (i = 0; i < HEAPSIZE; i++) {
        H[0][i] = NULL;
        H[1][i] = NULL;
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

int myAtoi(char* str){ // string to integer
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

void swapPatient (int h, int a, int b) { // swap a & b in heap h
    if (a <= 0 || a > N[h] || b <= 0 || b > N[h]) {
        printf("\e[33mWarning:\e[0m Swap argument(s) out of range. Request ignored. Result may not be creadible.\n");
        return ;
    }
    Patient *tmp = H[h][a];
    H[h][a] = H[h][b];
    H[h][b] = tmp;
    findPatient[H[h][a] -> ID % IDSCALE] = b;
    findPatient[H[h][b] -> ID % IDSCALE] = a;
}

int whoRules (Patient *a, Patient *b) { // compare priority
    if (!b) { // first argument has innate priority
        return 1;
    }
    if (!a && b) {
        return 2;
    }
    if (a -> level > b -> level) {
        return 1;
    }
    if (a -> level < b -> level) {
        return 2;
    }
    return a -> time < b -> time ? 1 : 2; // a, b are on same level
}

void enQ (char *name, int id, int lvl, int verbose) { // if verbose == 0, this is used for update
    Patient *p = (Patient*)malloc(sizeof(Patient));
    strcpy (p -> name, name);
    p -> ID = id;
    p -> level = lvl;
    T++;
    p -> time = T;
    if (verbose == 1) {
        printf("\e[35m%s\e[0m, \e[35m%d\e[0m, lvl.\e[35m%d\e[0m comes to queue.\n", name, id, lvl);
    }
    N[1]++;
    findPatient[id % IDSCALE] = N[1];
    H[1][N[1]] = p; // climb up the heap from bottom
    int i = N[1];
    while (i > 1 && whoRules (H[1][i / 2], H[1][i]) == 2) {
        swapPatient (1, i / 2, i);
        i /= 2;
    }
}

void rollDown (int h, int t) { // in heap h, target t is removed, then last patient rolls down from t
    Patient *p = H[h][t];
    swapPatient (h, t, N[h]); // roll down the heap from here
    findPatient[(p -> ID) % IDSCALE] = 0;
    free(p);
    H[h][N[h]] = NULL;
    N[h]--;
    int i = t;
    while (H[h][i * 2]) { // H will always be a complete binary heap
        if (whoRules (H[h][i], H[h][i * 2]) == 2 || whoRules (H[h][i], H[h][i * 2 + 1]) == 2) {
            if (whoRules (H[h][i * 2], H[h][i * 2 + 1]) == 1) { // swap with bigger child
                swapPatient (h, i, i * 2);
                i = i * 2;
            }
            else {
                swapPatient (h, i, i * 2 + 1);
                i = i * 2 + 1;
            }
        }
        else if (whoRules (H[h][i], H[h][i * 2]) == 2) {
            swapPatient (h, i, i * 2);
            i = i * 2;
        }
        else { // no need to roll down further
            break ;
        }
    }
}

Patient *deQ (int noprint) { // if noprint == 0, that means this deQ is used for printing
    if (!H[noprint][1]) {
        if (noprint == 1) {
            printf("No patients in the waiting line.\n");
        }
        return NULL;
    }
    Patient *p = H[noprint][1];
    if (noprint == 1) {
        printf("\e[35m%s\e[0m, \e[35m%d\e[0m, lvl.\e[35m%d\e[0m goes to the doctor.\n", p -> name, p -> ID, p -> level);
        fprintf(FOUT, "%s, %d\n", p -> name, p -> ID);
    }
    rollDown (noprint, 1);
    return p;
}

void quitQ (int id, int verbose) { // if verbose == 0, this is used for update
    int t = findPatient[id % IDSCALE];
    if (t == 0 && verbose == 1) {
        printf("No patient found by ID %d.\n", id);
        return ;
    }
    Patient *p = H[1][t];
    if (verbose == 1) {
        printf("\e[35m%s\e[0m, \e[35m%d\e[0m, lvl.\e[35m%d\e[0m quits the line.\n", p -> name, p -> ID, p -> level);
    }
    rollDown (1, t);
}

void update (int id, int lvl) {
    int t = findPatient[id % IDSCALE];
    if (t == 0) {
        printf("No patient found by ID %d.\n", id);
        return ;
    }
    Patient *p = H[1][t];
    printf("\e[35m%s\e[0m, \e[35m%d\e[0m, lvl.%d -> lvl.\e[35m%d\e[0m updated.\n", p -> name, p -> ID, p -> level, lvl);
    char name[NAMESIZE];
    strcpy (name, p -> name);
    quitQ (id, 0);
    enQ (name, id, lvl, 0);
}

void printQ () {
    printf("\e[36m╔════════════════════════════════════════\e[0m\n");
    if (N[1] == 0) {
        printf("No patients in the waiting line.\n");
    }
    else {
        Patient *p;
        N[0] = N[1];
        int i;
        printf("\e[36m║\e[0mWaiting list (with descending priority):\n");
        for (i = 1; i <= N[1]; i++) { // copy entire heap to heap for printing
            H[0][i] = (Patient*)malloc(sizeof(Patient));
            strcpy (H[0][i] -> name, H[1][i] -> name);
            H[0][i] -> ID = H[1][i] -> ID;
            H[0][i] -> level = H[1][i] -> level;
            H[0][i] -> time = H[1][i] -> time;
        }
        for (i = 1; i <= N[1]; i++) {
            p = deQ (0); // note that this only affect heap for printing
            if (p) {
                printf("\e[36m║\e[0m   %d. %s, %d, lvl.%d\n", i, p -> name, p -> ID, p -> level);
            }
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
            deQ (1);
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
