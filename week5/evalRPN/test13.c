#include"evalRPN.h"

int main(int argc, char** argv){
    char *tokenBank[56] = {"5", "1", "2", "+", "4", "*", "+", "3", "-", \
        "1", "2", "+", "4", "*", "5", "+", "3", "-", \
        "2", "1", "+", "3", "*", \
        "4", "13", "5", "/", "+", \
        "3","-4","+", \
        "5", "2", "+", "4", "*", "+", "3", \
        "5", "2", "+", "4", "*", "3", \
        "*", "2", "+", "4", "*", "3", \
        "5", "-", "2", "4", "*", "3"};
    int ref[10] = {14,14,9,6,-1,0,0,0,0,0};
    int tokensSize[10] = {9,9,5,5,3,0,7,6,6,6};
    int ans, j, k = 0;
    char **tokens;
    for (j = 0; j < 10; j++){
        int i;
        printf("Case %d\tInput: ",j+1);
        if (tokensSize[j] != 0){
            tokens = (char**)malloc(sizeof(char*)*tokensSize[j]);
            for (i = 0; i < tokensSize[j]; i++){
                tokens[i] = tokenBank[k];
                printf("\"%s\" ",tokens[i]);
                k++;
            }printf("\n");
        }else{
            tokens = NULL;
            printf("null\n");
        }
        ans = evalRPN(tokens,tokensSize[j]);
        printf("\tOutput: %d\tExpected: %d\n\n",ans,ref[j]);
    }
	system("pause");
    return 0;
}

/** Zhang Chen, Dept. EE, Fudan University, 2016 **/