/**
 * Given a string containing '(', ')', '{', '}', '[' and ']'
 * determine if the input string is valid. 
 * You may not change the input string. 
 * 
 * The brackets must close in the correct order. 
 * "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
 * 
 * Hint:
 * If the lastest unbalanced left bracket encountered is '(', 
 * then the next right bracket must be ')' in order to balance it.
 * To validate the input sentence, every left bracket should be 
 * balalenced with a right bracket, and every right bracket should
 * be able to balance the lastest unbalanced left bracket. 
 * 
 * One way to do it is to push every left bracket into the stack,
 * and pop the top element when encountering the correct right bracket. 
**/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>

bool isValid(char* s) {
/* Your code should start from here. */
    #define MAXLEN 500000
    int stack[MAXLEN] = {0}, head = 0, i;
    for (i = 0; i < strlen(s); i++) {
        if (head >= MAXLEN) {
            printf("StackOverflowError: string length exceeds %d.\n", MAXLEN);
            return false;
        }
        switch (s[i]) {
            case '(': // push left bracket into stack
                stack[head++] = 1;
                break;
            case '[':
                stack[head++] = 2;
                break;
            case '{':
                stack[head++] = 3;
                break;
            case ')': // pop corresbonding right bracket or fail
                if (head > 0 && stack[head - 1] == 1) {
                    head--;
                    break;
                }
                else {
                    return false;
                }
            case ']':
                if (head > 0 && stack[head - 1] == 2) {
                    head--;
                    break;
                }
                else {
                    return false;
                }
            case '}':
                if (head > 0 && stack[head - 1] == 3) {
                    head--;
                    break;
                }
                else {
                    return false;
                }
        }
    }
    if (head == 0) {
        return true;
    }
    else {
        return false;
    }

/* End of your code. */
}
