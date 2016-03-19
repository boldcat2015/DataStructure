#include"isValid.c"

int main(int argc, char** argv){
    char *str[12] = {\
    "for(t = p;*t&&((*t>='a'&&*t<='z')||(*t>='A'&&*t<='Z')||*t=='\'');t++)",\
    "for(t = p;*t&&((*t>='a'&&*t<='z')||(*t>='A'&&*t<='Z'||*t=='\'');t++)",\
    "if(*r>='A'&&*r<='Z')\n    voc[r-p] = *r+('a'-'A');\nelse\n    voc[r-p] = *r;",\
    "if(*r>='A'&&*r<='Z')\n    voc[r-p] = *r+('a'-'A');\nelse\n    voc(r-p] = *r;",\
    "DICT{\n    char *word;\n    int word_counter;\n    DICT *next_s;    // On the negative result of strcmp\n    DICT *next_l;    // based on the positive result of strcmp\n    DICT *next;    // get a linked list while setting up the binary tree\n};",\
    "DICT{\n    char *word;\n    int word_counter;\n    DICT *next_s;    // On the negative result of strcmp\n    DICT *next_l;    // based on the positive result of strcmp\n    DICT *next;    // get a linked list while setting up the binary tree\n;",\
    "{\n    for(i=0; i<dim; i+=block){\n        im = i+block;\n        for(j=0; j<dim; j+=block){\n            jm = j+block;for(i1=i; i1<im; i1++){\n                for(j1=j; j1<jm;j1++)\n                dst[RIDX(i1, j1, dim)] = src[RIDX(j1, dim-i1-1, dim)];\n            }\n        }\n    }\n}",\
    "{\n    for(i=0; i<dim; i+=block){\n        im = i+block;\n        for(j=0; j<dim; j+=block){\n            jm = j+block;for(i1=i; i1<im; i1++){\n                for(j1=j; j1<jm;j1++)\n                dst[RIDX(i1, j1, dim)] = src(RIDX(j1, dim-i1-1, dim)];\n            }\n        }\n    }\n}",\
    "for(j = 1;j<dim-1;j++){\n    dst[i2].red = (unsigned short)((src[i2-1].red+src[i3-1].red+\\\n    src[i2].red+src[i3].red+src[i2+1].red+src[i3+1].red)/6);\n    dst[i2].green = (unsigned short)((src[i2-1].green+src[i3-1].green+\\\n    src[i2].green+src[i3].green+src[i2+1].green+src[i3+1].green)/6);\n    dst[i2].blue = (unsigned short)((src[i2-1].blue+src[i3-1].blue+\\\n    src[i2].blue+src[i3].blue+src[i2+1].blue+src[i3+1].blue)/6);i2++,i3++;\n}",\
    "for (j = 1;j<dim-1;j++ {\n    dst[i2].red = (unsigned short)((src[i2-1].red+src[i3-1].red+\\\n    src[i2].red+src[i3].red+src[i2+1].red+src[i3+1].red)/6);\n    dst[i2].green = (unsigned short)((src[i2-1].green+src[i3-1].green+\\s\n    rc[i2].green+src[i3].green+src[i2+1].green+src[i3+1].green)/6);\n    dst[i2].blue = (unsigned short)((src[i2-1].blue+src[i3-1].blue+\\\n    src[i2].blue+src[i3].blue+src[i2+1].blue+src[i3+1].blue)/6);i2++,i3++;\n}",\
    "team_t team = {\n    /* Team name */\n    /* First member's full name */\n    /* First member's email address */\n    /* Second member's full name (leave blank if none) */\n    /* Second member's email address (leave blank if none) */\n};",\
     "team_t team = \n    /* Team name */\n    /* First member's full name */\n    /* First member's email address */\n    /* Second member's full name (leave blank if none) */\n    /* Second member's email address (leave blank if none) */\n};"};
    int i,score = 0;
    bool ret;
    for (i = 0; i < 12; i++){
        printf("Input:\n*******\n%s\n*******\n",str[i]);
        ret = isValid(str[i]);
        printf("Output:");
        if(ret) printf("true");
        else printf("false");
        printf("\tExpected:");
        if(i%2) printf("false\n");
        else printf("true\n\n");
        if (ret == !(i%2))  score++;
        if(i%2) system("pause(1)");
    }
    printf("Score:\t%d / 12\n",score);
    return 0;
}

/** Zhang Chen, Dept. EE, Fudan University, 2016 **/
