// File encoding with UTF-8
// Please compile with -std=c99
//
// Week 1 Assignment 1
// 2016.02.29
// 程雨歌 12307110079
// Aim: to find if the given array contains any duplicates.
// Algorithm: quickSort the array, then check if there are identical adjacent elements.

#include <stdio.h>
#include <stdlib.h> // for function malloc
#include <string.h> // for function memcpy
#include <stdbool.h> // for type Bool

void quickSort(int*, int, int);
int roughSort(int*, int, int);
bool containsDuplicate(int*, int); // key function of this assignment
void verbose(int*, int);

int main(int argc, const char* argv[])
{
    int a[] = {7, 12, 1, -2, 0, 15, 4, 11, 9};
    verbose(a, 9);
    int b[] = {9, 12, 1, -4, 0, 15, 4, 11, 9};
    verbose(b, 9);
    verbose(b, 9);
    return 0;
}

void quickSort(int* a, int l, int r)
{
    int m; // location of the pivot of roughSort
    if (l < r)
    {
        m = roughSort(a, l, r); // divide and conquer
        quickSort(a, l, m - 1);
        quickSort(a, m + 1, r);
    }
}

int roughSort(int* a, int l, int r) // bifurcate, increasingly
{
    int pivot, i, j, t;
    pivot = a[l];
    i = l; j = r + 1;
    while(1)
    {
        while(a[i] <= pivot && i <= r) i++;
        while(a[j] > pivot && j >= l) j--;
        if ( i >= j ) break;
        t = a[i]; a[i] = a[j]; a[j] = t;
    }
    t = a[l]; a[l] = a[j]; a[j] = t; // swap pivot to middle
    return j;
}

bool containsDuplicate(int* nums, int numsSize)
{
    int* a = malloc(numsSize * sizeof(int)); // get a copy to keep given array untouched
    memcpy(a, nums, numsSize * sizeof(int));
    quickSort(a, 0, numsSize - 1);
    int i;
    for (i = 0; i < numsSize - 2; i++)
        if (a[i] == a[i + 1])
        {
            free(a);
            return true;
        }
    free(a);
    return false;
}

void verbose(int* nums, int numsSize)
{
    int i;
    printf("\n{");
    for(i = 0; i < numsSize - 1; i++)
        printf("%d, ", nums[i]);
    printf("%d}\n", nums[i]);
    if (containsDuplicate(nums, numsSize))
        printf("CONTAINS duplicate(s).\n");
    else
        printf("contains NO duplicates.\n");
}
