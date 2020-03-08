#ifndef _CALC_H_
#define _CALC_H_

#define LINE(i) ((i)/9)
#define ROW(i) ((i)%9)
#define BLOCK(i) (LINE(i)/3*3 + ROW(i)/3)

#define NO_NUM -1

/*  確定した数字num
    候補のフラグkouho*/
struct masu_s{
    int num;
    int kouho[9];
} masu[81];

void reset();
void showAllTest();
void showAllKouho(int);
int sumKouho(int);
void checkNum(int);
void checkNumAll();
int lineStart(int);
int rowStart(int);
int blockStart(int);
void dltKouho(int, int);
void deleteLine(int);
void deleteRow(int);
void deleteBlock(int);
void inputNum(int, int);
int isFindKouho(int, int);
int isOnlyOneInLine(int, int);
int isOnlyOneInRow(int, int);
int isOnlyOneInBlock(int, int);
int isOnlyOne(int, int);

#endif