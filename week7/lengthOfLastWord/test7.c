#define _CRT_SECURE_NO_WARNINGS 1
#include"lengthOfLastWord.h"

int main(int argc, char** argv){
    char *str[NUMCASE] = {"At",\
    "  Thursday s",\
    "Republican      presidential debate",\
    "Trump     ",\
    "was confronted with those past quotes",\
    "and asked about the ugly  nature",\
    "  of the events he s been leading   ",\
    " He said that he hoped that his audiences",\
    " wouldn",\
    "",\
    " ",\
    " t ",\
    "resort to violence",\
    " And he said he wouldn t condone it when it happens ",\
    " But naturally he framed it as misunderstood       "};
    int ref[NUMCASE] = {2,1,6,5,6,6,7,9,6,0,0,1,8,7,13};
    int i, ret, score = 0;
    char s[100];
    for (i = 0; i < NUMCASE; i++){
        strcpy(s,str[i]);
        printf("%2d/15:\tInput:\t\"%s\"\n",i+1,s);
        ret = lengthOfLastWord(s);
        printf("\tOutput:\t%d\t",ret);
        printf("Expected:%d",ref[i]);
		printf("\t%s\n\n",ret==ref[i]?"Correct!":"Incorrect...");
        if (ret == ref[i])
            score ++;
		if(i == 4 || i == 9)
			system("pause");
    }printf("Correctness:\t%d/ %d\n",score,NUMCASE);
	system("pause");
    return 0;
}

/** Zhang Chen, Dept. EE, Fudan University, 2016 **/