#include"myAtoi.h"

int main(int argc, char** argv){
    int i, score = 0, bonus = 0;
    /* 16 test cases. */
    char *numsStr[17] = \
    {"0","-0","1","+1","-1","+-2","010","123 456","    -1df ","99","-199",\
    "a123","   xyz   ","2147483648","-2147483649","    10522545459","    -10522545459"};
    int reference[17] = \
    {0,0,1,1,-1,0,10,123,-1,99,-199,0,0,0x7fffffff,0x80000000,0x7fffffff,0x80000000};  
    /* Test */
    for (i = 0; i < 17; i++){
        int num = myAtoi(numsStr[i]);
        printf("Case %d\tInput:\t%s\n\tOutput: %d\tExpected: %d\n\n",\
            i+1,numsStr[i],num,reference[i]);
        if (num == reference[i])
            i < 13? score++:bonus++;
    }
    printf("Correctness: %2d / 13 + %d\n",score,bonus);
	system("pause");
    return 0;
}

/** Zhang Chen, Dept. EE, Fudan University, 2016 **/