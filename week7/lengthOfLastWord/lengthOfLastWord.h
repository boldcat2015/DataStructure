/**
 * Given a string s consists of upper/lower-case alphabets and
 * empty space characters ' ', return the length of last word in the string.
 * If the last word does not exist, return 0.
 * 
 * Note: A word is defined as a character sequence consists of non-space
 * characters only. You are allowed to change the input string. 
 * 
 * For example, 
 * Given s = "Hello World",
 * return 5.
**/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NUMCASE 15

int lengthOfLastWord(char* s) {
/* Your cdoe should start here. */
    if (!s) {
        return 0;
    }
    int c = 0, inword = 0, i;
    for (i = 0; i < strlen(s); i++) {
        if (s[i] != ' ' && s[i] != '\t') {
            if (!inword) { // begin a new word
                inword = 1;
                c = 0;
            }
            c++;
        }
        else {
            inword = 0;
        }
    }
    return c;

/* End of your cdoe. */
}
