/* This file solves Question 1.3 in Project A,
 * in course Data Structure, 2016 spring.
 *
 * Tasks:
 * Reconstruct binary search tree from preorder and inorder result,
 * output postorder result of the mirror tree,
 * and # of nodes with 2 children.
 *
 * Solution:
 * 1. Mark the first element of the preorder result as root,
 * 2. mark the root element in the inorder result,
 * 3. root will divide the inorder result into left sub tree and right sub tree.
 * 4. repeat above steps with preorder and inorder result of sub trees.
 *
 * May 2016, Cheng Yuge, Fudan University
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 256
FILE *FIN, *FOUT;
char Pre[BUFFSIZE][BUFFSIZE], In[BUFFSIZE][BUFFSIZE]; // preorder & inprder result of entire tree
int N; // N = total number of Nodes.

typedef struct Node { // tree node
    char val[BUFFSIZE];
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode (char *v) {
    Node* newNode;
    newNode = (Node*)malloc(sizeof(Node));
    strcpy (newNode -> val, v);
    newNode -> left = NULL;
    newNode -> right = NULL;
    return newNode;
}

void init () { // initialize: get Preorder & Inorder
    FIN = fopen("./input3.txt", "r");
    FOUT = fopen("./output3.txt", "w+");
    if ( !FIN ) {
        printf("Failed to open input3.txt.\n");
        exit(1);
    }
    int i, s;
    char buff[BUFFSIZE]; 
    if (fgets(buff, BUFFSIZE, FIN)) {
        printf("buff = %s", buff);
        for (i = 0, s = -1, N = 0; buff[i]; i++) { // get Preorder result
            if (s == -1 && buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\n') {
                s = i; // a new word starts here.
            }
            if (s != -1 && (buff[i] == ' ' || buff[i] == '\t' || buff[i] == '\n')) {
                strncpy (Pre[N], &buff[s], i - s); // word ends here.
                s = -1;
                printf("Pre[%d] = %s\n", N, Pre[N]);
                N++;
            }
        }
    }
    else {
        printf("No input content detected.\n");
        exit(2);
    }
    if (fgets(buff, BUFFSIZE, FIN)) {
        printf("buff = %s", buff);
        int n;
        for (i = 0, s = -1, n = 0; buff[i]; i++) { // get Inorder result
            if (s == -1 && buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\n') {
                s = i; // a new word starts here.
            }
            if (s != -1 && (buff[i] == ' ' || buff[i] == '\t' || buff[i] == '\n')) {
                strncpy (In[n], &buff[s], i - s); // word ends here.
                s = -1;
                printf("In[%d] = %s\n", n, In[n]);
                n++;
            }
        }
        if (n != N) {
            printf("Numbers of elements in Preorder & Inorder don't match.\n");
            exit(3);
        }
    }
    else {
        printf("No inorder result detected.\n");
        exit(4);
    }
}

int findRoot (char *val, int start, int len) { // find the index of val in In within possible len
    int i;
    for (i = start; i - start < len; i++) {
        if (strcmp(In[i], val) == 0) {
            return i;
        }
    }
    printf("%s not found in Inorder.\n", val);
    exit(5);
    return -1;
}

Node* reconstruct (int preS, int inS, int len) { // S = start point, len = length of both
    Node *root = createNode (Pre[preS]);
    int mid = findRoot (Pre[preS], inS, len);
    int lLen = mid - inS; // length of left sub tree
    int rLen = len - lLen - 1; // length of right sub tree
    if (lLen > 0) {
        root -> left = reconstruct (preS + 1, inS, lLen);
    }
    if (rLen > 0) {
        root -> right = reconstruct (preS + lLen + 1, mid + 1, rLen);
    }
    return root;
}

void draw (Node *root, int d) { // draw the tree, just for checking.
    if (root -> right) {
        draw (root -> right, d + 1);
    }
    int i;
    for (i = 0; i < d; i++) {
        printf("   ");
    }
    printf("%s\n", root -> val);
    if (root -> left) {
        draw (root -> left, d + 1);
    }
}

void post (Node *root) { // output postorder result of tree
    if (root -> right) {
        post (root -> right);
    }
    if (root -> left) {
        post (root -> left);
    }
    fprintf(FOUT, "%s ", root -> val);
    printf("%s ", root -> val);
}

int countBoth (Node *root) { // count the total number of tree nodes with 2 children
    int count = 0;
    if (root -> left && root -> right) {
        count++;
    }
    if (root -> left) {
        count += countBoth (root -> left);
    }
    if (root -> right) {
        count += countBoth (root -> right);
    }
    return count;
}

int main () {
    init ();
    Node *root = reconstruct (0, 0, N);
    printf ("\nBehold the reconstructed tree: (up = right)\n");
    draw (root, 0);
    printf ("Postorder result of the mirror tree:\n");
    post (root);
    fprintf (FOUT, "\b\n");
    printf ("\nwhich should be identical with the reversed preorder result of the original tree:\n");
    int i;
    for (i = N - 1; i >= 0; i--) {
        printf ("%s ", Pre[i]);
    }
    printf ("\b\n");

    int c; // # of nodes with 2 children
    c = countBoth (root);
    fprintf (FOUT, "%d\n", c);
    printf ("\nNumber of nodes with 2 children: %d\n", c);

    fclose (FIN);
    fclose (FOUT);
    return 0;
}
/* End of file */
