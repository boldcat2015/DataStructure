/* This file solves Question 4 in Project A,
 * in course Data Structure, 2016 spring.
 *
 * Tasks:
 *     read in 2 positive numbers: x and y, then compute x + y, x - y, x * y, and x ^ y if y is a integer.
 *
 * Solution:
 *     x + y and x - y are simple implementation digit by digit,
 *     x * y use Karatsuba algorithm, a method of divide & conquer
 *     x ^ y use method of dividing y recursively: x ^ y = x ^ y/2 * x ^ y
 * Note that numbers containing dot are considered non-integer, such as 5.0, 5., etc.
 *
 * May 2016, Cheng Yuge, Fudan University
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 1048576
#define MAXLEN 1048576
FILE *FIN, *FOUT;

typedef struct Num {
    int len;
    int digit[MAXLEN];
    int dot; // how many digits are there after dot. dot == 0 implies integer.
    int sign;
    int isInt;
} Num;

Num zero = {
    .len = 1,
    .digit = {0},
    .dot = 0,
    .sign = 1,
    .isInt = 1};

void init ();
void initNum (Num*);
void readNum (Num*, char*, int, int);
void printNum (Num*, int);
void cutNum (Num*, Num*, int, int);
Num *paste (Num*, int);
Num *minus (Num*);
int compareNum (Num*, Num*);
Num *fracToInt (Num*);
Num *intToFrac (Num*, int);
Num *karastuba (Num*, Num*);
Num *divideTwo (Num*);
Num *add (Num*, Num*);
Num *substract (Num*, Num*);
Num *multiply (Num*, Num*);
Num *power (Num*, Num*);
void mainLoop ();

int main () {
    init ();
    mainLoop ();
    fclose (FIN);
    fclose (FOUT);
    return 0;
}

void init () {
    printf("start initializing...\n");
    FIN = fopen("./input4.txt", "r");
    FOUT = fopen("./output4.txt", "w+");
    if ( !FIN ) {
        printf("\e[31mFailed to open input4.txt.\e[0m\n");
        exit(1);
    }
    printf("\e[32msuccessfully opened input4.txt.\e[0m\n");
}

void initNum (Num *n) {
    if (!n) { printf("\e[33mWarning:\e[0m Initialize NULL.\n");
        return ;
    }
    int i;
    n -> len = 0;
    for (i = 0; i < MAXLEN; i++) {
        n -> digit[i] = 0;
    }
    n -> dot = 0;
    n -> sign = 1;
    n -> isInt = 1;
}

void readNum (Num *n, char *src, int start, int end) {
    if (!n || !src || start < 0 || start >= end) {
        printf("\e[31mError:\e[0m Failed to read in number.\n");
        exit (3);
    }
    int i, j = 0;
    initNum (n);
    for (i = end - 1; i >= start; i--) {
        if (src[i] == '.') {
            if (n -> isInt == 0) {
                printf("\e[31mError:\e[0m Too many dots. Please validate input.\n");
                exit (4);
            }
            n -> isInt = 0;
            n -> dot = j;
        }
        else if (src[i] >= '0' && src[i] <= '9') { // digit[0] is lowest
            n -> digit[j] = (int)(src[i] - '0');
            j++;
            n -> len ++;
        }
        else {
            printf("\e[31mError:\e[0m Too many numbers. Please validate input.\n");
            exit (5);
        }
    }
}

void cutNum (Num *n, Num *src, int start, int end) {
    if (!n || !src || start < 0 || start >= end) {
        printf("\e[31mError:\e[0m Failed to cut up number.\n");
        exit (3);
    }
    int i;
    initNum (n);
    for (i = start; i < end; i++) {
        n -> digit[i - start] = src -> digit[i];
    }
    n -> len = end - start;
    for (i = n -> len - 1; i > 0 && n -> digit[i] == 0; i--) { // erase leading 0's
        n -> len --;
    }
}

Num *paste (Num *n, int d) {
    if (!n) {
        printf("\e[31mError:\e[0m NULL when pasting.\n");
        exit (6);
    }
    Num *ans = (Num*)malloc(sizeof(Num));
    initNum (ans);
    int i;
    for (i = 0; i < n -> len; i++) {
        ans -> digit[i + d] = n -> digit[i];
    }
    ans -> len = n -> len + d;
    ans -> sign = n -> sign;
    for (i = ans -> len - 1; i > 0 && ans -> digit[i] == 0; i--) { // erase leading 0's
        ans -> len --;
    }
    return ans;
}

void printNum (Num *n, int ttyonly) {
    if (!n) {
        printf("\e[33mWarning:\e[0m Printing NULL.\n");
        return ;
    }
    int i;
    if (n -> sign == -1) {
        printf("-");
        if (ttyonly == 0) {
            fprintf(FOUT, "-");
        }
    }
    for (i = n -> len - 1; i >= 0; i--) {
        printf("%d", n -> digit[i]);
        if (ttyonly == 0) {
            fprintf(FOUT, "%d", n -> digit[i]);
        }
        if (n -> isInt == 0 && n -> dot == i && n -> dot != 0) {
            printf(".");
            if (ttyonly == 0) {
                fprintf(FOUT, ".");
            }
        }
    }
    /*
    if (n -> isInt == 1) {
        printf(" is integer,");
    }
    printf(" len = %d, dot = %d", n -> len, n -> dot);
    */
}

Num *minus (Num *n) { // minus (n) = -n
    if (!n) {
        printf("\e[31mError:\e[0m NULL when minusing.\n");
        exit (6);
    }
    Num *ans = (Num*)malloc(sizeof(Num));
    initNum (ans);
    ans -> len = n -> len;
    int i;
    for (i = 0; i < n -> len; i++) {
        ans -> digit[i] = n -> digit[i];
    }
    ans -> dot = n -> dot;
    ans -> isInt = n -> isInt;
    ans -> sign = -1 * n -> sign;
    return ans;
}

int compareNum (Num *a, Num *b) { // < = > | -1 0 1
    if (!a || !b) {
        printf("\e[31mError:\e[0m NULL when comparing.\n");
        exit (6);
    }
    if (a -> sign == -1 && b -> sign == 1) {
        return -1;
    }
    if (a -> sign == 1 && b -> sign == -1) {
        return 1;
    }
    if (a -> sign == -1 && b -> sign == -1) {
        return -1 * compareNum (minus(a), minus(b));
    }
    if (a -> len - a -> dot > b -> len - b -> dot) {
        return 1;
    }
    if (a -> len - a -> dot < b -> len - b -> dot) {
        return -1;
    }
    // now a & b are positive, have same scale
    int i, d = a -> len - b -> len;
    for (i = a -> len - 1; i >= 0 && i - d >= 0 ; i--) {
        if (a -> digit[i] > b -> digit[i - d]) {
            return 1;
        }
        if (a -> digit[i] < b -> digit[i - d]) {
            return -1;
        }
    }
    // now a & b are identical within the common part
    if (a -> len > b -> len) { // even if the longer part are tailing 0's!
        return 1; // but the tailing 0's are avoided in add & substract
    }
    if (a -> len < b -> len) { // it is a matter of precision
        return -1;
    }
    return 0; // finally
}

Num *fracToInt (Num *n) {
    if (!n) {
        printf("\e[31mError:\e[0m NULL when fracToInting.\n");
        exit (6);
    }
    Num *ans = (Num*)malloc(sizeof(Num));
    initNum (ans);
    ans -> len = n -> len;
    int i;
    for (i = 0; i < n -> len; i++) {
        ans -> digit[i] = n -> digit[i];
    }
    for (i = ans -> len - 1; i >= 0 && ans -> digit[i] == 0; i--) { // erase leading 0's
        ans -> len --;
    }
    ans -> dot = 0;
    ans -> isInt = 1;
    ans -> sign = n -> sign;
    return ans;
}

Num *intToFrac (Num *n, int d) {
    if (!n) {
        printf("\e[31mError:\e[0m NULL when intToFracing.\n");
        exit (6);
    }
    Num *ans = (Num*)malloc(sizeof(Num));
    initNum (ans);
    int i, j;
    ans -> isInt = 0;
    ans -> sign = n -> sign;
    ans -> len = n -> len;
    for (i = 0; i < n -> len; i++) {
        ans -> digit[i] = n -> digit[i];
    }
    ans -> dot = d;
    if (ans -> dot + 1 > ans -> len) { // leading 0's already exist :)
        ans -> len = ans -> dot + 1;
    }
    for (i = 0; i < ans -> dot && ans -> digit[i] == 0; i++); // erase tailing 0's
    for (j = 0; j < ans -> len; j++) {
        ans -> digit[j] = ans -> digit[j + i];
    }
    ans -> len -= i;
    ans -> dot -= i;
    return ans;
}

Num *karastuba (Num *a, Num *b) {
    if (!a || !b) {
        printf("\e[31mError:\e[0m NULL when multiplying.\n");
        exit (6);
    }
    if (a -> isInt == 0 || b -> isInt == 0) {
        printf("\e[31mError:\e[0m Non integer arg(s) when karastubaing.\n");
        exit (7);
    }
    Num *ans = (Num*)malloc(sizeof(Num));
    initNum (ans);
    if (a -> len <= 1000 && b -> len <= 1000) { // trivial case
        int i, j;
        for (i = 0; i < a -> len; i++) { // what we do in elementary schools
            for (j = 0; j < b -> len; j++) {
                ans -> digit[i + j] += a -> digit[i] * b -> digit[j];
            }
        }
        ans -> len = a -> len + b -> len;
        for (i = 0; i < ans -> len; i++) { // carry
            ans -> digit[i + 1] += ans -> digit[i] / 10;
            ans -> digit[i] %= 10;
        }
        for (i = ans -> len - 1; i > 0 && ans -> digit[i] == 0; i--) { // erase leading 0's
            ans -> len --;
        }
        return ans;
    }
    // now begin kernel of karastuba: divide & conquer.
    // visit wiki page for more information about notaions:
    // https://zh.wikipedia.org/wiki/Karatsuba%E7%AE%97%E6%B3%95
    Num *ahigh, *alow, *bhigh, *blow;
    Num *z0, *z1, *z2; // notation same to wiki page of karastuba
    Num *z11, *z12, *Lz11, *Lz12, *L1, *L2, *sum; // e.g. z11 & z12 are for z1
    // all these bunch of handles are just for freeing them.
    int m, l; // l is longer length, m to cut
    l = a -> len > b -> len ? a -> len : b -> len;
    m = l / 2;
    alow = (Num*)malloc(sizeof(Num));
    cutNum (alow, a, 0, m); // printf ("\nalow = "); printNum (alow, 1); system ("pause");
    blow = (Num*)malloc(sizeof(Num));
    cutNum (blow, b, 0, m); // printf ("\nblow = "); printNum (blow, 1); system ("pause");
    ahigh = (Num*)malloc(sizeof(Num));
    cutNum (ahigh, a, m, l); // printf ("\nahigh = "); printNum (ahigh, 1); system ("pause");
    bhigh = (Num*)malloc(sizeof(Num));
    cutNum (bhigh, b, m, l); // printf ("\nbhigh = "); printNum (bhigh, 1); system ("pause");
    z0 = karastuba (alow, blow); // printf ("\nz0 = "); printNum (z0, 1); system ("pause");
    z11 = add (alow, ahigh); // printf ("\nz11 = "); printNum (z11, 1); system ("pause");
    z12 = add (blow, bhigh); // printf ("\nz12 = "); printNum (z12, 1); system ("pause");
    z1 = karastuba (z11, z12); // printf ("\nz1 = "); printNum (z1, 1); system ("pause");
    z2 = karastuba (ahigh, bhigh); // printf ("\nz2 = "); printNum (z2, 1); system ("pause");
    Lz11 = substract (z1, z2); // printf ("\nLz11 = "); printNum (Lz11, 1); system ("pause");
    Lz12 = substract (Lz11, z0); // printf ("\nLz12 = "); printNum (Lz12, 1); system ("pause");
    L1 = paste (Lz12, m); // printf ("\nL1 = "); printNum (L1, 1); system ("pause");
    L2 = paste (z2, m * 2); // printf ("\nL2 = "); printNum (L2, 1); system ("pause");
    sum = add (L1, L2); // printf ("\nsum = "); printNum (sum, 1); system ("pause");
    ans = add (sum, z0); // printf ("\nans = "); printNum (ans, 1); system ("pause");
    free(alow); free(blow); free(ahigh); free(bhigh); free(z0); free(z1); free(z2);
    free(z11); free(z12); free(Lz11); free(Lz12); free(L1); free(L2); free(sum);
    return ans;
}

Num *divideTwo (Num *n) {
    if (!n) {
        printf("\e[31mError:\e[0m NULL when divideTwoing.\n");
        exit (6);
    }
    Num *ans = (Num*)malloc(sizeof(Num));
    initNum (ans);
    ans -> len = n -> len;
    int i;
    for (i = 0; i < n -> len; i++) {
        ans -> digit[i] = ((n -> digit[i + 1] % 2) * 10 + n -> digit[i]) / 2;
    }
    ans -> dot = n -> dot;
    ans -> isInt = n -> isInt;
    if (ans -> digit[ans -> len - 1] == 0) {
        ans -> len --;
    }
    return ans;
}

Num *add (Num *a, Num *b) { // only positive numbers are allowed
    if (!a || !b) {
        printf("\e[31mError:\e[0m NULL when adding.\n");
        exit (6);
    }
    Num *ans = (Num*)malloc(sizeof(Num)), *c, *d; // c = long(chang), d = short(duan)
    initNum (ans);
    ans -> sign = 1;
    if (a -> isInt == 1 && b -> isInt == 1) {
        ans -> isInt = 1;
    }
    else {
        ans -> isInt = 0;
    }
    if (a -> dot > b -> dot) {
        c = a;
        d = b;
    }
    else {
        c = b;
        d = a;
    }
    ans -> dot = c -> dot;
    int i, j, l, m;
    l = c -> dot - d -> dot; // how much c is longer than d after the point
    m = c -> len - c -> dot > d -> len - d -> dot ? c -> len - c -> dot : d -> len - d -> dot;
    m += c -> dot; // m or m + 1 will be ans -> len
    for (i = 0; i < m; i++) {
        if (i < l) { // only longer one has digit here
            ans -> digit[i] += c -> digit[i];
        }
        else { // both have digit
            ans -> digit[i] += c -> digit[i] + d -> digit[i - l];
            ans -> digit[i + 1] += ans -> digit[i] / 10;
            ans -> digit[i] %= 10;
        }
    }
    if (ans -> digit[m] == 0) {
        ans -> len = m;
    }
    else {
        ans -> len = m + 1;
    }
    for (i = 0; i < ans -> dot && ans -> digit[i] == 0; i++);
    for (j = 0; j < ans -> len; j++) {
        ans -> digit[j] = ans -> digit[j + i];
    }
    ans -> len -= i;
    ans -> dot -= i;
    return ans;
}

Num *substract (Num *a, Num *b) {
    if (!a || !b) {
        printf("\e[31mError:\e[0m NULL when substracting.\n");
        exit (6);
    }
    Num *ans;
    if (a -> sign == 1 && b -> sign == -1) {
        Num *mb = minus (b);
        ans = add (a, mb);
        free (mb);
        return ans;
    }
    if (a -> sign == -1 && b -> sign == 1) {
        Num *ma = minus (a);
        Num *t = add (ma, b);
        ans = minus (t);
        free (ma); free (t);
        return ans;
    }
    if (a -> sign == -1 && b -> sign == -1) {
        Num *ma = minus (a);
        Num *mb = minus (b);
        ans = substract (mb, ma);
        free (ma); free (mb);
        return ans;
    }
    // now a & b are positive
    ans = (Num*)malloc(sizeof(Num));
    initNum (ans);
    Num *c, *d, *e, *f; // c chang d duan, e - f >= 0
    if (a -> isInt == 1 && b -> isInt == 1) {
        ans -> isInt = 1;
    }
    else {
        ans -> isInt = 0;
    }
    if (a -> dot > b -> dot) { // just for l & m
        c = a;
        d = b;
    }
    else {
        c = b;
        d = a;
    }
    ans -> dot = c -> dot;
    int i, j, l, m;
    l = c -> dot - d -> dot; // how much c is longer than d after the point
    m = c -> len - c -> dot > d -> len - d -> dot ? c -> len - c -> dot : d -> len - d -> dot;
    m += c -> dot; // m is total length of aligned two number a & b
    ans -> len = m;
    if (compareNum (a, b) == -1) {
        ans -> sign = -1;
        e = b;
        f = a;
    }
    else {
        ans -> sign = 1;
        e = a;
        f = b;
    }
    for (i = 0; i < m; i++) {
        if (i < l) { // only longer one has digit here
            if (e == c) { // longer is bigger
                ans -> digit[i] += e -> digit[i];
            }
            else {
                ans -> digit[i] += -(f -> digit[i]);
            }
        }
        else { // both have digit
            if (e == c) {
                ans -> digit[i] += e -> digit[i] - f -> digit[i - l];
            }
            else {
                ans -> digit[i] += e -> digit[i - l] - f -> digit[i];
            }
        }
        if (ans -> digit[i] < 0) { // borrow 1 from higher digit
            ans -> digit[i] += 10;
            ans -> digit[i + 1] += -1;
        }
    }
    for (i = m - 1; i > 0 && i > ans -> dot && ans -> digit[i] == 0; i--) { // erase leading 0's
        ans -> len --;
    }
    for (i = 0; i < ans -> dot && ans -> digit[i] == 0; i++); // erase tailing 0's
    for (j = 0; j < ans -> len; j++) {
        ans -> digit[j] = ans -> digit[j + i];
    }
    ans -> len -= i;
    ans -> dot -= i;
    return ans;
}

Num *multiply (Num *a, Num *b) {
    if (!a || !b) {
        printf("\e[31mError:\e[0m NULL when multiplying.\n");
        exit (6);
    }
    if (compareNum (a, &zero) == 0 || compareNum (b, &zero) == 0) {
        Num *ans = (Num*)malloc(sizeof(Num));
        initNum (ans);
        ans -> isInt = a -> isInt * b -> isInt;
        ans -> sign = a -> sign * b -> sign;
        ans -> len = 1;
        return ans;
    }
    Num *ans, *a0, *b0, *c;
    a0 = fracToInt (a); // convert to integers and use karastuba
    b0 = fracToInt (b);
    int d = a -> dot + b -> dot;
    c = karastuba (a0, b0);
    ans = intToFrac (c, d); // add the decimal point back
    ans -> isInt = a -> isInt * b -> isInt;
    ans -> sign = a -> sign * b -> sign;
    free (a0); free (b0); free (c);
    return ans;
}

Num *power (Num *a, Num *b) {
    if (!a || !b) {
        printf("\e[31mError:\e[0m NULL when powering.\n");
        exit (6);
    }
    Num *ans = (Num*)malloc(sizeof(Num));
    initNum (ans);
    int i;
    if (compareNum (a, &zero) == 0) { // 0 ^ b = 0
        ans -> len = 1;
        return ans;
    }
    if (compareNum (b, &zero) == 0) { // a ^ 0 = 1
        ans -> len = 1;
        ans -> digit[0] = 1;
        return ans;
    }
    if (b -> len == 1 && b -> digit[0] == 1) { // a ^ 1 = a
        ans -> len = a -> len;
        for (i = 0; i < ans -> len; i++) {
            ans -> digit[i] = a -> digit[i];
        }
        ans -> sign = a -> sign;
        ans -> dot = a -> dot;
        ans -> isInt = a -> isInt;
        return a;
    }
    if (b -> len == 1 && b -> digit[0] == 2) { // a ^ 2 = a * a
        return multiply (a, a);
    }
    Num *half, *p, *m;
    half = divideTwo (b);
    p = power (a, half);
    printf("\n");
    if (b -> digit[0] % 2 == 0) {
        ans = multiply (p, p);
        printNum (a, 1); printf(" ^ "); printNum (b, 1); printf(" =\n");
        printNum (a, 1); printf(" ^ "); printNum (half, 1); printf(" ^ 2 = ");
        printNum (ans, 1); printf("\n");
        return ans;
    }
    else {
        m = multiply (p, p);
        ans = multiply (m, a);
        printNum (a, 1); printf(" ^ "); printNum (b, 1); printf(" =\n");
        printNum (a, 1); printf(" ^ "); printNum (half, 1); printf(" ^ 2 * ");
        printNum (a, 1); printf(" = ");
        printNum (ans, 1); printf("\n");
        return ans;
    }
}

void mainLoop () {
    char buff[BUFFSIZE], c;
    int i, m = -1, l = 0, L;
    while (fgets(buff, BUFFSIZE, FIN)) {
        l++;
        L = strlen(buff);
        printf("line %d: buff = %s", l, buff);
        for (i = 0; i < L; i++) {
            c = buff[i];
            if (!(c >= '0' && c <= '9') && c != '.' && c != ' ' && c != '\t' && c != '\n') {
                printf("\e[31mError:\e[0m Encountered illegal character, on line %d, column %d. Only digit, dot (in half-width) and space are allowed.\n", l, i);
                exit (2);
            }
            if (c == ' ' && c != '\t') { // x & y are seperated here
                m = i;
            }
        }
        Num *x = (Num*)malloc(sizeof(Num));
        Num *y = (Num*)malloc(sizeof(Num));
        Num *sum, *diff, *times, *expo;
        if (m != -1) {
            // printf("read from 0 to %d:\n", m);
            readNum (x, buff, 0, m);
            int eol;
            if (buff[L - 1] != '\n' && buff[L - 1] != '\r') { // no \r or \n at eol
                eol = L;
            }
            else if (buff[L - 2] != '\n' && buff[L - 2] != '\r') { // \r or \n
                eol = L - 1;
            }
            else if (buff[L - 3] != '\n' && buff[L - 2] != '\r') { // \r\n or \n\r
                eol = L - 2;
            }
            else {
                printf("\e[31mError:\e[0m Strange EOL on line %d. Line skipped.\n", l);
                continue ;
            }
            // printf("read from %d to %d:\n", m + 1, eol);
            readNum (y, buff, m + 1, eol); // need more test on different operation systems.
        }
        else {
            printf("\e[33mWarning:\e[0m Not enough number on line %d. Line skipped.\n", l);
            continue ;
        }
        x = add (x, &zero); y = add (y, &zero); // formalize
        sum = add (x, y); printf("x + y = ");
        printNum (sum, 0); free (sum); // x + y
        diff = substract (x, y); printf("\nx - y = "); fprintf(FOUT, " ");
        printNum (diff, 0); free (diff); // x - y
        times = multiply (x, y); printf("\nx * y = "); fprintf(FOUT, " ");
        printNum (times, 0); free (times); // x * y
        if (y -> isInt == 1 && y -> sign == 1) {
            expo = power (x, y); printf("\nx ^ y = "); fprintf(FOUT, " ");
            printNum (expo, 0); free (expo); // x ^ y
        }
        printf("\n\n"); fprintf(FOUT, "\n");
        free (x); free (y);
        m = -1;
        // system ("pause");
    }
}
/* End of file */
