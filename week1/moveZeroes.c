// File encoding with UTF-8
//
// Week 1 Assignment 2
// 2016.02.29
// 程雨歌 12307110079
// Aim: to move all 0's to the end of the given array while maintaining the relative order of the non-zero elements.
// Algorithm: move the non-zero elements to front and queue.

#include <stdio.h>

void moveZeroes(int*, int);

int main(int argc, const char* argv[])
{
    int a[] = {0, 1, 0, 3, 12, -4, 0, 0, 89};
    int i;
    printf("\nBefore:\n");
    for (i = 0; i < 9; i++) printf("%d ", a[i]);
    moveZeroes(a, 9);
    printf("\nAfter:\n");
    for (i = 0; i < 9; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}

void moveZeroes(int* nums, int numsSize)
{
    int i, j;
    for (j = 0; j < numsSize && nums[j] != 0; j++);
    for (i = j + 1; i < numsSize; i++)
        if (nums[i] != 0)
        {
            nums[j] = nums[i];
            nums[i] = 0;
            j++;
        }
}
