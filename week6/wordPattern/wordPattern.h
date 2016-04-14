/**
 * Given a string <pattern> and a string <str>, 
 * find if <str> follows the same <pattern>.
 * 
 * Here, "follow" means a full match, 
 * such that there is a bijection between
 * a letter in pattern and a non-empty word in str.
 * 
 * Examples:
 * pattern = "abba", str = "dog cat cat dog" should return true.
 * pattern = "abba", str = "dog cat cat fish" should return false.
 * pattern = "aaaa", str = "dog cat cat dog" should return false.
 * pattern = "abba", str = "dog dog dog dog" should return false.
 * 
 * Notes:
 * You may assume pattern contains only lowercase letters,
 * and str contains lowercase letters separated by a single space.
**/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int bool;
#define false 0
#define true 1

bool wordPattern(char* pattern, char* str) {
/* Your implementation of wordPattern should start from here. */
    if (!pattern && !str) { // vacant true
        // printf("vacant true.\n");
        return true;
    }
    int psize = 0;
    int ssize = 0;
    if (pattern) {
        psize = strlen(pattern);
    }
    if (str) {
        ssize = strlen(str);
    }
    if ((!str && psize == 0) || (!pattern && ssize == 0)) { // one is NULL and the other is ""
        return true;
    }
    if (!str || !pattern) { // one is NULL but the other is not ""
        return false;
    }
    int i, j, k, l;
    /* First: check same patterns must have same words. */
    int *check = malloc(sizeof(int) * psize); // record first appearance of this pattern
    for (i = 0; i < psize; i++) {
        for (j = 0; j <= i; j++) {
            if (pattern[i] == pattern[j]) {
                check[i] = j;
                break;
            }
        }
    }
    /* // build check table: lead to the number of pattern first appears.
    printf("check:\n");
    for (i = 0; i < psize; i++) {
        printf("%d ", check[i]);
    }
    printf("\n");
    */
    int *whead = malloc(sizeof(int) * psize); // record head position of each word
    int word = 0; // now it's the word-th word
    for (i = 0; i < ssize; i++) {
        while (i < ssize - 1 && (str[i] == ' ' || str[i] == '\t')) { // skip to next word
            i++;
        }
        if (i == ssize - 1 && (str[i] == ' ' || str[i] == '\t')) { // str ends with blank
            break;
        }
        word++;
        if (word > psize) { // more words than patterns.
            // printf("more words than patterns.\n");
            free(check); free(whead);
            return false;
        }
        whead[word - 1] = i;
        if (check[word - 1] == word - 1) { // pattern appears for the first time
            while (i < ssize && str[i] != ' ' && str[i] != '\t') { // skip to next blank
                i++;
            }
            continue;
        }
        else { // compare
            for (j = whead[word - 1]; i < ssize && str[i] != ' ' && str[i] != '\t'; j++, i++) {
                if (str[i] != str[j]) { // mismatch
                    // printf("mismatch : str[%d] = %c != str[%d] = %c.\n",\
                    // i, str[i], j, str[j]);
                    free(check); free(whead);
                    return false;
                }
            }
        }
    }
    if (word < psize) { // more patterns than words.
        // printf("more patterns than words.\n");
        free(check); free(whead);
        return false;
    }
    /* Second: check same words must have same patterns. */
    for (i = 0; i < word; i++) {
        for (j = 0; j < i; j++) {
            for (k = whead[i], l = whead[j]; k < ssize && str[k] != ' ' && str[k] != '\t' ;\
                    k++, l++) {
                if (str[k] != str[l]) { // not same word
                    break;
                }
            }
            if ((k > ssize || str[k] == ' ' || str[k] == '\t') && \
                    (str[l] == ' ' || str[l] == '\t')) { // i & j are same word
                if (check[i] != check[j]) { // they don't have the same pattern
                    // printf("word %d & word %d should have same pattern.\n", j + 1, i + 1);
                    free(check); free(whead);
                    return false;
                }
            }
        }
    }
    free(check); free(whead);
    return true; // all patterns match
/* End of your code. */
}
