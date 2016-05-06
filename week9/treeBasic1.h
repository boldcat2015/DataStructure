/**
 * In this assignment you are required to finish two simple functions. 
 * 1. <createTreeOnArray>
 *    Create a binary search tree based on an input array. 
 *    You need to guarentee that the left node is smaller than the parent, 
 *    and that the right node is bigger. On reoccurence, you need to ignore 
 *    later entries, so that no two nodes of the tree have the same value. 
 * 2. <printTree>
 *    You may use either Pre-Order Traversal, In-Order Traversal, 
 *    or Post-Order Traversal to visualize the tree you just created. 
 *    Your results should be able to show the structure of the tree. 
 *    That being said, special attention is required to be paid on 
 *    indent. nodes of the same depth should have identical indent. 
 * 
 * Node: 
 *    When creating a tree, all tree nodes, including the root, 
 *    should be malloced.
 * 
 * Hints:
 *    Naturally, when traversing trees, we apply recursion. 
 *    In <printTree>, the only input parameter is root pionter 
 *    of the tree. Since You are not supposed to write other 
 *    functions in assistance, it's impossible to send depth 
 *    information between recursions. However, depth is a very 
 *    important information in this task. One way to solve this
 *    confict is to use static variables. 
 *    https://en.wikipedia.org/wiki/Static_variable
 *    
**/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct treeNode{
    int val;
    struct treeNode *left;
    struct treeNode *right;
};
/* Libraries and definition of struct treeNode. */

struct treeNode* createTreeOnArray(int* nums, int numsSize){
 /* Your implementation of createTree should start here. */
    if (!nums || numsSize <= 0) {
        return NULL;
    }
    #define MAXVAL 100
    int i, v, hash[MAXVAL] = {0};
    struct treeNode *root = malloc(sizeof(struct treeNode)), *p;
    root -> val = nums[0];
    root -> left = NULL;
    root -> right = NULL;
    hash[nums[0]] = 1;
    for (i = 1; i < numsSize; i++) {
        v = nums[i];
        if (hash[v] != 0) { // reoccurence
            // printf("Reoccurence of %2d.\n", v);
            continue;
        }
        p = root;
        // printf("inserting %2d...\n", v);
        /* traverse to bottom */
        while ((v < p -> val && p -> left) || (v > p -> val && p -> right)) {
            // printf(" -> %2d", p -> val);
            if (v < p -> val) {
                p = p -> left;
            }
            else {
                p = p -> right;
            }
        }
        // printf(" -> %2d", p -> val);
        if (v < p -> val) {
            // printf("inserted left.\n");
            p -> left = (struct treeNode *)malloc(sizeof(struct treeNode));
            p = p -> left;
        }
        else {
            // printf("inserted right.\n");
            p -> right = (struct treeNode *)malloc(sizeof(struct treeNode));
            p = p -> right;
        }
        p -> val = v;
        p -> left = NULL;
        p -> right = NULL;
        hash[v] = 1;
    }
    return root;
 /* End of your createTree. */
}

void printTree(struct treeNode* root){
 /* Your implementation of printTree should start here. */
    if (!root) {
        printf("   \e[31m(null)\e[0m\n");
        return;
    }
    #define MAXQUEUE 21
    #define DEPTH 21
    #define WIDTH 80
    char map[DEPTH][WIDTH] = {""}; // We will draw this.
    struct treeNode *q[MAXQUEUE]; // Queue for BFS.
    int pos[MAXQUEUE]; // Position of node, in full-bi-tree label.
    int t = 0, n = 1, i, j, k;
    q[0] = root;
    pos[0] = 1;
    while (t < n) { // BFS to get position of each node.
        if (q[t] -> left) {
            q[n] = q[t] -> left;
            pos[n] = pos[t] * 2;
            n++;
        }
        if (q[t] -> right) {
            q[n] = q[t] -> right;
            pos[n] = pos[t] * 2 + 1;
            n++;
        }
        t++;
    } // now n = total number of nodes in tree.
    for (t = 0; t < n; t++) {
        // printf("%2d @ %d\n", q[t] -> val, pos[t]);
        for (i = DEPTH - 1; i >= 0; i--) {
            if (pos[t] & (1 << i)) {
                break; // node is on line i.
            }
        }
        j = ((pos[t] - (1 << i) + 1) * 2 - 1) * WIDTH / (1 << (i + 1)); // row j
        // printf("%2d @ (%2d,%2d)\n", q[t] -> val, i, j);
        map[i * 2][j] = q[t] -> val % 10 + '0';
        map[i * 2][j - 1] = q[t] -> val / 10 == 0 ? ' ' : q[t] -> val / 10 + '0';
        if (q[t] -> left) { // draw left branch
            map[i * 2 + 1][j] = 'L'; // Left only
            k = ((pos[t] * 2 - (1 << (i + 1)) + 1) * 2 - 1) * WIDTH / (1 << (i + 2));
            map[i * 2 + 1][k] = 'l'; // is left child
            for (k = k + 1; k < j; k++) {
                map[i * 2 + 1][k] = '-';
            }
        }
        if (q[t] -> right) { // draw right branch
            map[i * 2 + 1][j] = 'R'; // Right only
            k = ((pos[t] * 2 - (1 << (i + 1)) + 2) * 2 - 1) * WIDTH / (1 << (i + 2));
            map[i * 2 + 1][k] = 'r'; // is right child
            for (k = k - 1; k > j; k--) {
                map[i * 2 + 1][k] = '-';
            }
        }
        if (q[t] -> left && q[t] -> right) {
            map[i * 2 + 1][j] = 'b'; // bifercate (or both)
        }
    }
    for (i = 0; i < DEPTH; i++) { // now DRAW!
        for (j = 0; j < WIDTH; j++) {
            if (!map[i][j]) {
                printf(" ");
            }
            else {
                switch (map[i][j]) {
                    case '-':
                        printf("\e[34m─\e[0m"); // blue for line
                        break;
                    case 'L':
                        printf("\e[34m┘\e[0m");
                        break;
                    case 'R':
                        printf("\e[34m└\e[0m");
                        break;
                    case 'l':
                        printf("\e[34m┌\e[0m");
                        break;
                    case 'r':
                        printf("\e[34m┐\e[0m");
                        break;
                    case 'b':
                        printf("\e[34m┴\e[0m");
                        break;
                    default:
                        printf("\e[32m%c\e[0m", map[i][j]); // green for node
                }
            }
        }
        printf("\n");
    }
    return;
 /* End of your printTree. */
}
