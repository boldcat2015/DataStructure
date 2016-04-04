/**
 * Requirements:
 * Implement atoi to convert a string to an integer.
 * 1. The function first discards as many whitespace characters
 *    as necessary until the first non-whitespace character is found.
 *    Then, starting from this character, takes an optional initial
 *    plus or minus sign followed by as many numerical digits as possible,
 *    and interprets them as a numerical value. 
 * 2. The string can contain additional characters after those that
 *    form the integral number, which are ignored and have no effect
 *    on the behavior of this function. 
 * 3. If the first sequence of non-whitespace characters in str is not
 *    a valid integral number, or if no such sequence exists because
 *    either str is empty or it contains only whitespace characters, 
 *    no conversion is performed. 
 * 4. If no valid conversion could be performed, a zero value is returned. 
 * ===================== ** BONUS ** =====================
 * If the correct value is out of the range of representable values, 
 * INT_MAX (2147483647) or INT_MIN (-2147483648) is returned. 
 * Please refer to the last three test cases.
 * 
 * Notes: 
 * 1. It is intended for this problem to be specified vaguely 
 *    (ie, no given input specs). You are responsible to gather
 *    all the input requirements up front.
 * 2. You may be excepting some warnings when compiling. 
 *    Just ignore it. 
 * 3. You may NOT change the input string. 
 * 4. You may NOT call built-in functions such as atoi and atol.
**/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int myAtoi(char* str){
/* Your implementation of atoi should start here. */
    if (!str) {
        return 0 ;
    }
    int ans = 0 , n = strlen( str ), i, sign = 0 , start = -1 ;
    char c;
    /* first discard prefix whitespaces */
    for (i = 0, c = str[i]; i < n && (c == ' ' || c == '\t' || c == '\n'); i++, c = str[i]);
    for ( ; i < n; i++) {
        c = str[i];
        if (start == -1) { /* deal with the optional sign symbol */
            if (c == '+') {
                sign = 1 ;
                start = i ;
            }
            else if (c == '-') {
                sign = -1 ;
                start = i ;
            }
            else if ((int)c >= (int)('0') && (int)c <= (int)('9')) {
                start = i ;
                ans = (int)c - (int)('0');
            }
            else {
                return 0 ;
            }
        }
        else if ((int)c >= (int)('0') && (int)c <= (int)('9')) {
            /* check if out of bounce */
            if (sign == -1 && ((ans == 214748364 && (int)c > 7 )|| ans > 214748364) ) {
                return 0x80000000 ;
            }
            else if ((ans == 214748364 && (int)c > 6 )|| ans > 214748364) {
                return 0x7fffffff ;
            }
            /* update ans */
            ans *= 10 ;
            ans += (int)c - (int)('0') ;
        }
        else {
            break ;
        }
    }
    if (sign == -1) {
        ans *= -1 ;
    }
    return ans ;
/* End of your implementation. */
}
