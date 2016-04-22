#include<time.h>
#include"sparseMatrixMultiplication.h"

int** createSparseMat(int, int, int);
void freeSparseMat(int**, int);
void printMat(int**,int,int);
void printTSMatrix(TSMatrix*);
int main(int argc, char** argv){
    TSMatrix *matA, *matB, *matC;
    ElemType **arrA, **arrB, **arrC;
    int rowSize,midSize,colSize, threshold;
    int i,j,k;
    ElemType tmp;
    srand(time(NULL));
 while(1){   
    /* case 1 Valid input */
    
    printf("Case 1: Valid input\n");
    rowSize = 1 + rand()%10;
    midSize = 1 + rand()%10;
    colSize = 1 + rand()%10;
    threshold = 6;
    arrA = createSparseMat(rowSize,midSize,threshold);
    arrB = createSparseMat(midSize,colSize,threshold);
    arrC = (int**)malloc(rowSize*sizeof(int*));
    for (i = 0; i < rowSize; i++)
        arrC[i] = (int*)calloc(colSize,sizeof(int));
    for (k = 0; k < midSize; k++)
        for (i = 0; i < rowSize; i++){
            tmp = arrA[i][k];
            for (j = 0; j < colSize; j++)
                    arrC[i][j] += tmp * arrB[k][j];
        }
    matA = createMat(arrA,rowSize,midSize);
    matB = createMat(arrB,midSize,colSize);
    printf("Matrix A:\n");
    printMat(arrA,rowSize,midSize);
    printf("Convert to:\n");
    printTSMatrix(matA);
    system("pause");
    printf("\nMatrix B:\n");
    printMat(arrB,midSize,colSize);
    printf("Convert to:\n");
    printTSMatrix(matB);
    system("pause");
    
    matC = multiMat(matA,matB);

    printf("\nYour Matrix C:\n");
    printTSMatrix(matC);
    printf("\nExpected:\n");
    printMat(arrC,rowSize,colSize);
    
    free(matA);
    free(matB);
    if(matC != NULL)
        free(matC);
    freeSparseMat(arrA,rowSize);
    freeSparseMat(arrB,midSize);
    freeSparseMat(arrC,rowSize);
    
    system("pause");
    
    /* case 2 Invalid input */
    
    printf("Case 2: Invalid input\n");
    rowSize = 1 + rand()%10;
    colSize = 1 + rand()%10;
    while(colSize == rowSize)
        colSize = 1 + rand()%10;
    threshold = 6;
    arrA = createSparseMat(rowSize,rowSize,threshold);
    arrB = createSparseMat(colSize,colSize,threshold);

    matA = createMat(arrA,rowSize,rowSize);
    matB = createMat(arrB,colSize,colSize);
    printf("Matrix A:\n");
    printMat(arrA,rowSize,rowSize);
    printf("Convert to:\n");
    printTSMatrix(matA);
    system("pause");
    printf("\nMatrix B:\n");
    printMat(arrB,colSize,colSize);
    printf("Convert to:\n");
    printTSMatrix(matB);
    system("pause");

    matC = multiMat(matA,matB);

    printf("\nYour Matrix C:\n");
    printTSMatrix(matC);
    printf("\nExpected: null\n");
    
    free(matA);
    free(matB);
    if(matC != NULL)
        free(matC);
    freeSparseMat(arrA,rowSize);
    freeSparseMat(arrB,colSize);
    system("pause");
 }
    return 0;
}

int** createSparseMat(int rowSize, int colSize, int threshold){
    int** arr = (int**)malloc(rowSize*sizeof(int*));
    int i,j,tmp;
    for (i = 0; i < rowSize; i++)
        arr[i] = (int*)calloc(colSize,sizeof(int));
    for(i = 0; i < rowSize; i++)
        for (j = 0; j < colSize; j++){
            tmp = rand()%10;
            if (tmp > threshold)
                arr[i][j] = tmp - threshold;
        }
    return arr;
}

void freeSparseMat(int** arr, int rowSize){
    int i;
    for (i = 0; i < rowSize; i++)
        free(arr[i]);
    free(arr);
}

void printMat(int** arr,int rowSize,int colSize){
    int i,j;
    for (i = 0; i < rowSize; i++){
        for (j = 0; j < colSize; j++){
            printf("%3d",arr[i][j]);
        }printf("\n");
    }
}

void printTSMatrix(TSMatrix* t){
    int i;
    if (t == NULL)
        printf("\tnull\n");
    else{
        printf("Row:%3d, Col:%3d, nums:%3d\n",t->rowSize,t->colSize, t->nums);
        for (i = 0; i < t->nums; i++)
            printf("(%d,%d):\t%d\n",t->data[i].row,t->data[i].col,t->data[i].val);
    }
}

/** Zhang Chen, Dept. EE, Fudan University, 2016 **/