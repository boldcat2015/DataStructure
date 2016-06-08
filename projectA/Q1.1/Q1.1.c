/* This file solves Question 1 in Project A,
 * in course Data Structure, 2016 spring.
 *
 * Tasks:
 * 1. Index words (case INsensitive) in the given passage in lexicographical order,
 * 2. code the characters (case SENSITIVE) for a Huffman tree according to appearance frequency.
 *
 * Solution:
 * Indexing:
 *     for each of 26 initials, insert words to the sorted chain.
 * Coding:
 *     1. count each character,
 *     2. build Huffman tree by merging 2 least frequency characters repeatedly,
 *     3. print the Huffman codes.
 *
 * May 2016, Cheng Yuge, Fudan University
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 1048576
#define HEAPSIZE 512
#define WORDLEN 256
#define CODELEN 128
#define ASCIISCALE 128
FILE *FIN, *DICT, *HUFF;

typedef struct Word { // words are linked in alphabetical order for each initial.
    int len;
    char word[WORDLEN];
    struct Word *next;
} Word;

typedef struct HtreeNode {
    char c;
    int sum;
    char code[CODELEN];
    struct HtreeNode *left;
    struct HtreeNode *right;
} HtreeNode;

Word alphabet[26]; // for indexing. They are meaningless head nodes.
int freq[ASCIISCALE] = {0}; // for coding
int totalC = 0; // total characters for calculate frequency
char code[ASCIISCALE][CODELEN] = {""}; // final Huffman code for each character. just for printing in alphabetical order
HtreeNode *Heap[HEAPSIZE]; // heap for generating huffman code
int N = 0; // total number of Huffman tree node

void init (); // open file & initialize dictionary heads.
int ord (char); // return alphabetic order of x: A/a = 0
int compareWord (Word*, Word*); // determine who should come first in lexicographical order
void insertWord (int, Word*); // with insert sorting to his family of same initial
void goLowerCase (Word *w);
void finNindexNcount ();
void buildHuffman ();
void printDict ();
void swapNode (int, int);
void push (HtreeNode*);
HtreeNode *pop ();
HtreeNode *combine (HtreeNode*, HtreeNode*);
void draw (HtreeNode*, int); // draw the tree, just for checking.
void assignCode (HtreeNode*, char*); // along the built Huffman tree
void buildHuffman ();
void printHuff ();

int main () {
    init ();
    finNindexNcount ();
    buildHuffman ();
    printDict ();
    printHuff ();
    fclose (FIN);
    fclose (DICT); fclose (HUFF);
    return 0;
}

void init () { // open file & initialize dictionary heads.
    printf("start initializing...\n");
    FIN = fopen("./input1.txt", "r");
    DICT = fopen("./dictionary.txt", "w+");
    HUFF = fopen("./huffman.txt", "w+");
    if ( !FIN ) {
        printf("\e[31mFailed to open input1.txt.\e[0m\n");
        exit(1);
    }
    printf("\e[32msuccessfully opened input1.txt.\e[0m\n");
    int i;
    for (i = 0; i < 26; i++) {
        alphabet[i].next = NULL;
    }
    for (i = 0; i < HEAPSIZE; i++) {
        Heap[i] = NULL;
    }
    printf("\e[32msuccessfully initialized dictionary and heap.\e[0m\n");
}

int ord (char x) { // return alphabetic order of x: A/a = 0
    if (x >= 'A' && x <= 'Z') {
        return (int)(x) - (int)('A');
    }
    if (x >= 'a' && x <= 'z') {
        return (int)(x) - (int)('a');
    }
    return -1; // not a letter.
}

int compareWord (Word *a, Word *b) { // determine who should come first in lexicographical order
    int la = a -> len;
    int lb = b -> len;
    int i;
    for (i = 0; i < (la < lb ? la : lb); i++) {
        if (ord(a -> word[i]) < ord(b -> word[i])) {
            return 1; // first word comes first
        }
        if (ord(a -> word[i]) > ord(b -> word[i])) {
            return 2; // second word comes first
        }
    }
    if (la == lb) {
        return 0; // two words are identical
    }
    return la < lb ? 1 : 2; // shorter word comes first
}

void insertWord (int initial, Word *w) { // with insert sorting to his family of same initial
    Word *prev = &alphabet[initial];
    Word *nx = prev -> next;
    while (nx && compareWord(nx, w) == 1) { // w should come later
         prev = prev -> next;
         nx = prev -> next;
    }
    if (!nx) { // w is last
        prev -> next = w;
        w -> next = NULL;
        printf("inserted at tail.\n");
        return;
    }
    if (compareWord(nx, w) == 0) { // w already exists
        printf("'\e[35m%s\e[0m' \e[33malready exists, didn't insert.\e[0m\n", w -> word);
        return; // do nothing
    }
    if (compareWord(nx, w) == 2) { // w comes before nx
        prev -> next = w;
        w -> next = nx;
        printf("inserted before '%s'.\n", nx -> word);
    }
    return;
}

void goLowerCase (Word *w) {
    int i;
    for (i = 0; i < w -> len; i++) {
        if (w -> word[i] >= 'A' && w -> word[i] <= 'Z') {
            w -> word[i] = w -> word[i] - 'A' + 'a';
        }
    }
}

void finNindexNcount () {
    char buff[BUFFSIZE];
    Word *newWord;
    int i, s, l = 0;
    while (fgets(buff, BUFFSIZE, FIN)) {
        l++;
        printf("line %d: buff = %s", l, buff);
        for (i = 0, s = -1; i < strlen(buff) && buff[i]; i++) {
            if ((int)(buff[i]) > 127 || (int)(buff[i]) < 0) {
                printf("\e[33mWarning:\e[0m encountered insoluble character, on line %d, column %d.\n", l, i);
                continue ;
                // exit(2);
            }
            freq[(int)(buff[i])]++;
            totalC++;
            if (s == -1 && ord(buff[i]) != -1) { // a new word starts here.
                s = i;
            }
            if (s != -1 && ord(buff[i]) == -1) { // word ends here.
                newWord = (Word*)malloc(sizeof(Word));
                newWord -> len = i - s;
                strncpy (newWord -> word, &buff[s], i - s);
                printf("\e[32minsert:\e[0m '%s'... ", newWord -> word);
                goLowerCase (newWord);
                insertWord(ord(newWord -> word[0]), newWord); // insert to his family
                s = -1;
            }
        }
    }
}

void printDict () {
    printf("\nDictionary:\n");
    int i;
    Word *p;
    for (i = 0; i < 26; i++) {
        p = alphabet[i].next;
        if (p) {
            fprintf(DICT, "%c:", 'A' + i);
            printf("%c:", 'A' + i);
            while (p) {
                fprintf(DICT, " %s", p -> word);
                printf("%s ", p -> word);
                p = p -> next;
            }
            fprintf(DICT, "\n");
            printf("\n");
        }
    }
}

void swapNode (int a, int b) {
    if (!Heap[a] || !Heap[b]) {
        printf("\e[33mWarning:\e[0m Swap argument(s) out of range. Request ignored. Result may not be creadible.\n");
        return ;
    }
    HtreeNode *tmp = Heap[a];
    Heap[a] = Heap[b];
    Heap[b] = tmp;
    return ;
}

void push (HtreeNode* p) {
    if (!p) {
        return ;
    }
    printf("\e[32mpush: \e[35m%c\e[0m:%d: %s ...\n", p -> c, p -> sum, p -> code);
    N++;
    Heap[N] = p;
    int i = N; // climb up from bottom
    while (i > 1 && Heap[i] -> sum < Heap[i / 2] -> sum) {
        swapNode (i, i / 2);
        i /= 2;
    }
}

HtreeNode *pop () {
    if (!Heap[1]) {
        return NULL;
    }
    HtreeNode *p = Heap[1];
    swapNode (1, N); // last node rolls down from top
    Heap[N] = NULL;
    N--;
    int i = 1;
    while (Heap[i * 2]) {
        if (Heap[i * 2 + 1] && Heap[i * 2 + 1] -> sum < Heap[i * 2] -> sum \
                && Heap[i * 2 + 1] -> sum < Heap[i] -> sum) { // roll right
            swapNode (i, i * 2 + 1);
            i = i * 2 + 1;
        }
        else if (Heap[i * 2] -> sum < Heap[i] -> sum) { // roll left
            swapNode (i, i * 2);
            i = i * 2;
        }
        else { // no need to roll down more
            break ;
        }
    }
    return p;
}

HtreeNode *combine (HtreeNode *a, HtreeNode *b) {
    HtreeNode *root = (HtreeNode*)malloc(sizeof(HtreeNode));
    root -> left = a;
    root -> right = b;
    root -> sum = a -> sum + b -> sum;
    root -> c = '\0';
    return root;
}

void draw (HtreeNode *root, int d) { // draw the tree, just for checking.
    if (root -> right) {
        draw (root -> right, d + 1);
    }
    int i;
    for (i = 0; i < d; i++) {
        printf("   ");
    }
    printf("\e[35m%c\e[0m:%d: %s\n", root -> c, root -> sum, root -> code);
    if (root -> left) {
        draw (root -> left, d + 1);
    }
}

void assignCode (HtreeNode *root, char *c) {
    if (!root) {
        return ;
    }
    strcpy (root -> code, c);
    if (root -> c) { // write to the code table for printing
        strcpy (code[(int)(root -> c)], c);
    }
    if (root -> left) {
        char *lc = malloc(strlen(c) + 1);
        strcpy (lc, c);
        strcat (lc, "0");
        assignCode (root -> left, lc);
        free (lc);
    }
    if (root -> right) {
        char *rc = malloc(strlen(c) + 1);
        strcpy (rc, c);
        strcat (rc, "1");
        assignCode (root -> right, rc);
        free (rc);
    }
}

void buildHuffman () {
    printf("building Huffman tree...\n");
    int i;
    HtreeNode *p;
    for (i = 32; i < 127; i++) { // all printable characters
        if (freq[i]) {
            p = (HtreeNode*)malloc(sizeof(HtreeNode));
            p -> c = (char)i;
            p -> sum = freq[i];
            strcpy (p -> code, "");
            p -> left = NULL;
            p -> right = NULL;
            push (p);
        }
    }
    printf("\e[32mAll characters in the heap.\e[0m Start merging by lowest frequency..\n");
    while (Heap[1] && Heap[2]) { // Heap not empty & has more than 1 nodes
        push (combine (pop(), pop()));
    }
    printf("assigning Huffman code along the Huffman tree...\n");
    assignCode (Heap[1], "");
    printf("\e[32mBehold the Huffman tree:\e[0m\n");
    draw (Heap[1], 0);
}

void printHuff () { printf("\nHuffman code:\n");
    int i;
    for (i = 32; i < 128; i++) { // all printable characters
        if (freq[i]) {
            fprintf(HUFF, "%c: %.6lf %s\n", i, (double)freq[i]/(double)totalC, code[i]);
            printf("%c: %d / %d = %.6lf %s\n", i, freq[i], totalC, (double)freq[i]/(double)totalC, code[i]);
        }
    }
}
/* End of file */
