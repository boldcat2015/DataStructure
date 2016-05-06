#include "treeBasic.h"

int main(int argc, char** argv){
    int *nums = NULL;
    int numsSize;
    struct treeNode *root;
    srand(time(NULL));
    numsSize = rand() % 20;
    printf("Input:\t");
    if (numsSize != 0){
        int i;
        nums = (int*)malloc(numsSize*sizeof(int));
        for (i = 0; i < numsSize; i++){
            nums[i] = rand() % 100;
            printf("%3d",nums[i]);
        }printf("\n");
    }else{
        printf("null\n");
    }
    root = createTreeOnArray(nums,numsSize);
    printf("Output:\n");
    printTree(root);
    system("pause");
    return 0;
}

/** Zhang Chen, Dept. EE, Fudan University, 2016 **/
