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
    #define MAXDEPTH 21
    static int D = 0; // Depth for indentation
    static int c[MAXDEPTH] = {0}; // record which child of parent it is
    if (root -> left) { // print left tree recursively
        D++;
        c[D] = 1;
        printTree(root -> left);
        D--;
    }
    int i;
    for (i = 0; i < D - 1; i++) {
        if (c[i + 1] != c[i + 2]) {
            printf(" \e[34m│\e[0m "); // blue for branches
        }
        else {
            printf("   ");
        }
    }
    if (D == 0) { // green for root
        printf("\e[32m%2d\e[0m\n", root -> val);
    }
    else {
        if (c[D] == 1) { // is left child
            printf("\e[34m ┌─\e[36m%2d\e[0m\n", root -> val); // indigo for nodes
        }
        else if (c[D] == 2) { // is right child
            printf("\e[34m └─\e[36m%2d\e[0m\n", root -> val);
        }
    }
    if (root -> right) { // print right tree recursively
        D++;
        c[D] = 2;
        printTree(root -> right);
        D--;
    }
    return;
 /* End of your printTree. */
}
