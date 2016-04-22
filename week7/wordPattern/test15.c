#define _CRT_SECURE_NO_WARNINGS 1 
#include"wordPattern.h"
#define NUMCASE 12

int main(int argc, char** argv){
    char *str[NUMCASE] = {"","","fdu",\
    "dog cat cat dog",\
    "dog cat cat fish",\
    "dog cat cat dog",\
    "dog dog dog dog",\
    "alice bob eve eve bob alice",\
    "alice bob eve alice bob",\
    "usc tandon ucsd utd tamu tamu ucsd usc tandon cmu ucsd ucsb ucla ucsd tamu",\
    "ufl tandon tandon scu stanford vanderbilt brown cmu ucsd nyu cmu ucla cmu",\
    "ucsd nyu columbia ucr uta ucsd cornell columbia duke umich usc usc upenn umn ucsd"};
    char *pattern[NUMCASE] = {"","a","","deed","abb","abcd","abba","xyzzyx","xyzxy",\
                            "utcdaacutmcslca","uttsavbcdnclc","uycrtuoldmsspnu"};
    bool ref[NUMCASE] = {1,0,0,1,0,0,0,1,1,1,1,0},ret;
    char patternArg[100],strArg[100];
    int i;
    for (i = 0; i < NUMCASE; i++){
        printf("%2d/10\tpattern:\"%s\"\n\tstr:\t\"%s\"\n",\
                i+1,pattern[i],str[i]);
        strcpy(patternArg,pattern[i]);
        strcpy(strArg,str[i]);
        ret = wordPattern(patternArg,strArg);
        if (ref[i] != ret){
            printf("\tExpected: %s\t\tIncorrect...\n",ref[i]?"True":"False");
            break;
        }else{
            printf("\tExpected: %s\t\tCorrect!\n\n",ref[i]?"True":"False");
        }
        if (i == 5)
            system("pause");
    }system("pause");
    return 0;
}

/** Zhang Chen, Dept. EE, Fudan University, 2016 **/