/**
 * Requiments:
 * 1. Given two sorted integer arrays nums1 and nums2,
 *    merge nums2 into nums1 as one sorted array.
 * 2. Think about the time complexity and space complexity
 *    of you function and write it in your report.
 * 
 * Note:
 * 1. You may assume that nums1 has enough space
 *    (size that is greater or equal to m + n)
 *    to hold additional elements from nums2.
 *    The number of elements initialized in nums1 and nums2
 *    are m and n respectively.
**/

#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void merge(int* nums1, int m, int* nums2, int n) {
/* Your code should start from here. */
    int i, j = 0, p;
    for (i = 0; i < m + j && j < n; i++) {
        if (nums2[j] < nums1[i]) { // insert current nums2 element before this
            for (p = m + j; p > i; p--) {
                nums1[p] = nums1[p - 1];
            }
            nums1[i] = nums2[j++];
        }
    }
    for (; j < n; j++) { // fill in rest of nums2
        nums1[i++] = nums2[j];
    }
/* End of your code. */
}

/* Warning: Testbench. PLEASE leave it INTACT. */
/* Warning: Testbench. PLEASE leave it INTACT. */
/* Warning: Testbench. PLEASE leave it INTACT. */

void printArray(int* , int);
void RandQuickSort(int*, int, int);

int main(int argc, char** argv){
    int nums1[14], nums2[14];
    int m[5] = {5,9,0,14,0}, n[5] = {9,5,0,0,14};
    int i, j;
    srand(time(NULL));
    for (i = 0; i < 5; i++){
        printf("Case%2d\n",i+1);
        /* Initialize the arrays. */
        for (j = 0; j < m[i]; j++)
            nums1[j] = rand()%100;
        for (j = 0; j < n[i]; j++)
            nums2[j] = rand()%100;
        RandQuickSort(nums1, 0, m[i]-1);
        RandQuickSort(nums2, 0, n[i]-1);
        printf("nums1:");
        printArray(nums1,m[i]);
        printf("nums2:");
        printArray(nums2,n[i]);
        // Test the merge function.
        merge(nums1, m[i], nums2, n[i]);
        printf("result:");
        printArray(nums1, m[i] + n[i]);
        printf("\n");
        
    }
    return 0;    
}

/* Print array nums of length numsSize. */
void printArray(int* nums, int numsSize){
    int i;
    for (i = 0; i< numsSize; i++)
        printf("%4d",nums[i]);
    printf("\n");
}

/* Randomized quicksort */
void RandQuickSort(int* nums, int m, int n){
    if(m >= n)
        return;
    else{
        int i, j;
        /* Pick a pivot randomly and put it at the head of the array. */
        int pivotLoc = m + rand() % (n - m);
        int pivot = nums[pivotLoc];
        nums[pivotLoc] = nums[m];
        nums[m] = pivot;
        /* The standard quicksort implementation. */
        for (j = m, i = m + 1; i <= n; i++){
            if(nums[i] <= pivot){
                int tmp = nums[++j];
                nums[j] = nums[i];
                nums[i] = tmp;
            }
        }
        nums[m] = nums[j];
        nums[j] = pivot;
        RandQuickSort(nums, m, j-1);
        RandQuickSort(nums, j+1, n);
        return;
    }
}

/** Zhang Chen, Dept. EE, Fudan University, 2016 **/
