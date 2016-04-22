/**
 * You are required to implement three functions:
 * 1. <creatMat>
 *    Creat a TSMatrix from a matrix input. 
 * 2. <findValue>
 *    Given a coordinate, find the corresponding value. 
 *    If there is an entry for the indices, return the value. Otherwise, return 0. 
 * 3. <multiMat>
 *    Impliment matrix multiplication operation on TSMatrix. 
 *    You are required to not only do the multiplication on legal inputs, 
 *    but also detect illegal inputs. 
 *    On legal input, your function should return the resulted TSMatrix. 
 *    On illegal input, your function should return NULL pointer. 
 * In your report, please focus your analysis on the latter two functions. 
 * 
 * Note:
 * 1. There may be some difference between the return types of functions in the assignments
 *    and that in the slides. Please strict to the assignment reqiremnts. 
 * 2. In <creatMat> and <multiMat>, the returned TSMatrix should be malloced, 
 *    You may expect <free> function in the testbench. 
 * 
 * Hints:
 * 1. You may call your <findValue> function when implimenting multiplication. 
 * 
 * 2. The definition of matrix multiplication is given by
 *        C(X*Z) = A(X*Y) * B(Y*Z)
 *        where C[i][j] = sum(A[i][k] * B[k][j]), k = 0,1,2,...,Y-1
 *    If we strictly follow the definition, we may end up code like
 *        for (i = 0; i < X; i++)
 *            for (j = 0; j < Z; j++)
 *                C[i][j] = 0;
 *                for (k = 0; k < Y; k++)
 *                    C[i][j] += A[i][k] * B[k][j];
 * 
**/
#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
typedef int ElemType;
typedef struct{
    int row;
    int col;
    ElemType val;
} TupNode;
typedef struct{
    int rowSize;
    int colSize;
    int nums;
    TupNode data[MaxSize];
} TSMatrix;
/* Definition of Sparse Matrix. */

TSMatrix* createMat(ElemType** mat, int rowSize, int colSize){
/* Create a TSMatrix from a 2D array. */
    if (!mat || rowSize <= 0 || colSize <= 0) {
        return NULL;
    }
    int i, j;
    TSMatrix *tsmat = malloc(sizeof(TSMatrix));
    tsmat -> rowSize = rowSize;
    tsmat -> colSize = colSize;
    tsmat -> nums = 0;
    // printf("row=%d, col=%d\n", tsmat -> rowSize, tsmat -> colSize);
    for (i = 0; i < rowSize; i++) {
        for (j = 0; j < colSize; j++) {
            if (mat[i][j] != 0) {
                tsmat -> data[tsmat -> nums].row = i;
                tsmat -> data[tsmat -> nums].col = j;
                tsmat -> data[tsmat -> nums].val = mat[i][j];
                /*
                printf("#%2d:(%2d,%2d)=%2d\n",tsmat -> nums, \
                        tsmat -> data[tsmat -> nums].row, \
                        tsmat -> data[tsmat -> nums].col, \
                        tsmat -> data[tsmat -> nums].val);
                */
                tsmat -> nums++;
            }
        }
    }
    return tsmat;
/* End of your <createMat> */
}

ElemType findValue(TSMatrix *t, int i, int j){
/* Find a value based on (i,j) coordinate. Return 0 if no value is found. */
    if (i < 0 || j < 0 || !t) {
        return 0;
    }
    if (i >= t -> rowSize || j >= t -> colSize || t -> nums == 0) {
        return 0;
    }
    int n = 0;
    while (n < t -> nums && t -> data[n].row < i) {
        n++;
    }
    if (n == t -> nums || t -> data[n].row > i) {
        return 0;
    }
    while (n < t -> nums && t -> data[n].row == i) {
        if (t -> data[n].col < j) {
            n++;
            continue;
        }
        else if (t -> data[n].col == j) {
            return t -> data[n].val;
        }
        else {
            return 0;
        }
    }
    return 0;
/* End of <findValue> */
}

TSMatrix* multiMat(TSMatrix *matA, TSMatrix *matB){
/* Your implimentation of matric multiplication here. */
    if (!matA || !matB) {
        return NULL;
    }
    if (matA -> colSize != matB -> rowSize) {
        return NULL;
    }
    if (matA -> rowSize <= 0 || matA -> colSize <= 0 || matB -> colSize <= 0) {
        return NULL;
    }
    int a, b, n, r = 0;
    ElemType** C = malloc(matA -> rowSize * sizeof(int*));
    for (n = 0; n < matA -> rowSize; n++) {
        C[n] = (int*)calloc(matB -> colSize,sizeof(int));
    }
    int* bH = calloc(matB -> rowSize + 1, sizeof(int));
    // bH mark the first TupNode of each row in matB
    for (n = 0; n < matB -> nums; n++) {
        for (; r <= matB -> data[n].row; r++) {
            bH[r] = n;
            // printf("bH[%d] = %d\n", r, n);
        }
    }
    bH[matB -> rowSize] = matB -> nums;
    for (a = 0; a < matA -> nums; a++) {
        for (b = bH[matA -> data[a].col]; b < bH[matA -> data[a].col + 1]; b++) {
            /* Thus every b has col same as row of a */
            C[matA -> data[a].row][matB -> data[b].col] += \
                matA -> data[a].val * matB -> data[b].val;
        }
    }
    TSMatrix* matC = createMat(C, matA -> rowSize, matB -> colSize);
    for (n = 0; n < matA -> rowSize; n++) {
        free(C[n]);
    }
    free(C);
    return matC;
/* End of your code. */
}
