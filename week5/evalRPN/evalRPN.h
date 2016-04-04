/**
 * Requirement:
 * Evaluate the value of an arithmetic expression in Reverse Polish Notation.
 * For more definition about RPN, please refer to 
 * http://en.wikipedia.org/wiki/Reverse_Polish_notation .
 * 
 * Valid operators are +, -, *, /. Each operand may be an integer or another expression.
 * Some examples:
 *   ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
 *   ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
 * 
 Note that there may be invalid inputs. On invalid inputs, your program should return 0.
 * 
 * ++++++++++++++ 
 * The algorithm for evaluating an standard arithmetic expression 
 * in Reverse Polish Notation is fairly straightforward:
 * 
 *  While there are input tokens left:
 *      read the next token from input.
 *      if (the token is a number)
 *          Push it onto the stack.
 *      else{
            Pop the top 2 number from the stack
 *          Evaluate the operator, with the values as arguments
 *          Push the returned results, if any, back onto the stack
 *      }
 *  Return the last value in the stack
 * ++++++++++++++   
 * 
 * Some examples:
 *   ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
 *   ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
 *   ["4", "13", "5",  "+"] -> 0 (extra number)
 *   ["+", "13", "5",  "+"] -> 0 (invalid operator)
**/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int evalRPN(char** tokens, int tokensSize){
/* Your implementation of evalRPN should start here. */
    if(!tokens) { /* NULL */
        // printf("\nError: NULL input\n");
        return 0 ;
    }
    #define MAXSIZE 500000
    int stack[MAXSIZE] = {0}, top = 0 , I;
    char *s ;
    int num , i, sign , start ;
    char c ;
    for (I = 0; I < tokensSize; I++) {
        s = tokens[I];
        if (!s) { /* empty token found! */
            // printf("\nError: empty token found!\n");
            return 0 ;
        }
        else if (strcmp(s,"+")==0||strcmp(s,"-")==0||strcmp(s,"*")==0||strcmp(s,"/")==0) {
            /* operator must be one of these four exact forms */
            if (top < 2) { /* invalid operator */
                // printf("\nError: invalid operator\n");
                return 0 ;
            }
            top -- ; /* pop 2 & push 1 */
            if (strcmp(s,"+")==0) {
                stack[top - 1] = stack[top - 1] + stack[top];
            }
            else if (strcmp(s,"-")==0) {
                stack[top - 1] = stack[top - 1] - stack[top];
            }
            else if (strcmp(s,"*")==0) {
                stack[top - 1] = stack[top - 1] * stack[top];
            }
            else if (strcmp(s,"/")==0) {
                stack[top - 1] = stack[top - 1] / stack[top];
            }
        }
        else { /* more tolerance toward numbers. Here Atoi s, implement from myAtoi.h */
            num = 0 ; start = -1 ; sign = 0 ;
            /* first discard prefix whitespaces */
            for (i = 0, c = s[i]; i < strlen(s) && (c == ' ' || c == '\t' || c == '\n'); i++, c = s[i]);
            for ( ; i < strlen(s) ; i++) {
                c = s[i];
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
                        num = (int)c - (int)('0');
                    }
                    else { /* unrecognized token */
                        // printf("\nError: unrecognized token\n");
                        return 0 ;
                    }
                }
                else if ((int)c >= (int)('0') && (int)c <= (int)('9')) {
                    /* check if out of bounce */
                    if (sign == -1 && ((num == 214748364 && (int)c > 7 )|| num > 214748364) ) {
                        num = 0x80000000 ;
                        // printf("\nWarning: exceed INT_MIN, -2147483648 substituded.\n");
                        break ;
                    }
                    else if ((num == 214748364 && (int)c > 6 )|| num > 214748364) {
                        num = 0x7fffffff ;
                        // printf("\nWarning: exceed INT_MAX, 2147483647 substituded.\n");
                        break ;
                    }
                    /* update num */
                    num *= 10 ;
                    num += (int)c - (int)('0') ;
                }
                else {
                    break ;
                }
            }
            if (sign == -1) {
                num *= -1 ;
            }
            if (top >= MAXSIZE) { /* stack overflow! */
                // printf("\nError: stack overflow!\n");
                return 0 ;
            }
            stack[top] = num ; /* push! */
            top ++;
        }
    }
    if (top > 1) { /* extra number */
        // printf("\nError: extra number\n");
        return 0 ;
    }
    else if (top == 1) { /* finally some meaningful result */
        return stack[0];
    }
    else { /* empty tokenbank, normally this condition would not happen */
        // printf("\nError: empty tokenbank\n");
        return 0 ;
    }

/* End of your implementation. */
}



