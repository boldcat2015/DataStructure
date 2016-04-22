// Knuth-Morris-Pratt Algorithm, directly implemented from Wikipedia
// Andy 2016.04.11
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void KMP_table(char *pattern, int *table) {
    if (!table)
        return;
    int psize = strlen(pattern);
    int pos = 2; // current position in pattern
    int next = 0;
    table[0] = -1;
    if (psize > 1) {
        table[1] = 0;
    }
    while (pos < psize) {
        if (pattern[pos - 1] == pattern[next]) { // substring continues
            // printf("continue @ %d.\n", pos);
            table[pos] = next + 1;
            next++;
            pos++;
        }
        else if (next > 0) { // fall back
            // printf("fall back to %d.\n", next);
            next = table[next];
        }
        else { // back to head
            // printf("back to head @ %d.\n", pos);
            table[pos] = 0;
            pos++;
        }
    }
    for (pos = 1; pos < psize; pos++) {
        while (table[pos] != -1 && pattern[pos] == pattern[table[pos]]) {
            table[pos] = table[table[pos]];
        }
    }
    return;
}

int KMP_search(char *target, char *pattern, int *table) {
    int tsize = strlen(target);
    int psize = strlen(pattern);
    int m = 0; // beginning of current matching in target
    int i = 0; // current position in pattern
    if (!table)
        return -1;
    while (m + i < tsize) {
        if (target[m + i] == pattern[i]) { // continue to match
            if (i == psize - 1) { // full matched
                return m;
            }
            i++;
        }
        else {
            if (table[i] > -1) { // shift
                m += i - table[i];
                i = table[i];
            }
            else { // need to start from head
                m++;
                i = 0;
            }
        }
    }
    return -1; // fail to match
}

int KMP(char *target, char *pattern) {
    int psize = strlen(pattern);
    int *table = malloc(sizeof(int) * psize);
    int i;
    KMP_table(pattern, table);
    // verbose
    if (table) {
        printf("table:\n%s\n", pattern);
        for (i = 0; i < psize; i++) {
            if (table[i] == -1) {
                printf("X");
            }
            else {
                printf("%d", table[i]);
            }
        }
    }
    int match = KMP_search(target, pattern, table);
    if (match >= 0) {
        printf("\nMatched @ %d:\n", match);
        printf("%s\n", target);
        for (i = 0; i < match; i++) {
            printf(" ");
        }
        printf("%s\n", pattern);
    }
    else {
        printf("\nNo matched.\n%s\n", target);
    }
    // end of verbose
    free(table);
    return match;
}

int main(int argc, const char *argv[]) {
    char target[] = "ABC ABCDAB ABCDABCDABDE";
    char pattern[] = "ABCDABD";
    int m = KMP(target, pattern);
    printf("%d\n", m);
    char S[] = "ababaabcbababc";
    char W[] = "ababababc";
    int n = KMP(S, W);
    printf("%d\n", n);
    return 0;
}
