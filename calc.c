#include <ncurses.h>
#include "calc.h"

void reset(){
    int i, j;
    move(0,0);
    for(i=0; i<81; i++){
        masu[i].num = NO_NUM;
        
        for(j=0; j<9; j++){
            masu[i].kouho[j] = 1;
        }
    }
}

void showAllTest(){
    int i;
    move(0,0);
    for(i=0;i<81;i++){
        if(masu[i].num > NO_NUM){
            /*表示なので+1する*/
            printw("[%d] ", masu[i].num + 1);
        }else{
            printw("[ ] ");
        }
        if(i%3==2)addstr("@ ");
        if(ROW(i) == 8)addch('\n');
        if(i%27==26){
            int j;
            for(j=0;j<41;j++)addch('=');
            addch('\n');
        }
    }
    refresh();
}

/* nをkouhoとするマスを表示 */
void showAllKouho(int n){
    int i;
    move(0,0);
    for(i=0;i<81;i++){
        if(masu[i].kouho[n] == 1 && masu[i].num == NO_NUM){
            /*  nがkouhoで空きマスのとき
                表示なので+1する*/
            attron(COLOR_PAIR(3));
            printw("<%d> ", n+1);
            attron(COLOR_PAIR(1));
        }else if(masu[i].kouho[n] == 1 && masu[i].num > NO_NUM){
            printw("[%d] ", n+1);
        }else{
            printw("[ ] ");
        }
        if(i%3==2)addstr("@ ");
        if(ROW(i) == 8)addch('\n');
        if(i%27==26){
            int j;
            for(j=0;j<41;j++)addch('=');
            addch('\n');
        }
    }
    refresh();
}

int sumKouho(int n){
    int i;
    int sum = 0;
    for(i=0; i<9; i++){
        sum += masu[n].kouho[i];
    }
    return sum;
}

void checkNum(int n){
    int i;
    if(sumKouho(n) == 1){
        for(i=0; i<9; i++){
            if(masu[n].kouho[i]){
                inputNum(n, i+1);
                return;
            }
        }
    }
    masu[n].num = NO_NUM;
}

void checkNumAll(){
    int i;
    for(i=0;i<81;i++){
        checkNum(i);
    }
}

int lineStart(int n){
    return LINE(n) * 9;
}

int rowStart(int n){
    return ROW(n) % 9;
}

int blockStart(int n){
    return LINE(n)/3*27 + ROW(n)/3*3;
}

void dltKouho(int n, int k_dlt){
    masu[n].kouho[k_dlt] = 0;
}

void deleteLine(int n){
    int i;
    int ls = lineStart(n);
    for(i=0; i<9; i++){
        if(ls+i == n){
            continue;
        }
        dltKouho(ls+i, masu[n].num);
    }
}

void deleteRow(int n){
    int i;
    int rs = rowStart(n);
    for(i=0; i<81; i+=9){
        if(rs+i == n){
            continue;
        }
        dltKouho(rs+i, masu[n].num);
    }
}

void deleteBlock(int n){
    int i, j;
    int bs = blockStart(n);
    for(i=0; i<27; i+=9){
        for(j=0; j<3; j++){
            if(bs+i+j == n){
                continue;
            }
            dltKouho(bs+i+j, masu[n].num);
        }
    }
}

/*  masu[n] に input0_9 を確定させる
    input0_9は0~9
    内部で input = input0_9 - 1 に変換  input0_9 = 0 のとき input = -1 */
void inputNum(int n, int input0_9){
    int i, input;
    input = input0_9 - 1;
    masu[n].num = input;
    for(i=0; i<9; i++){
        if(i == input)masu[n].kouho[i] = 1;
        if(i != input)masu[n].kouho[i] = 0;
    }
    if(input > NO_NUM){
        deleteLine(n);
        deleteRow(n);
        deleteBlock(n);
    }
}

int isFindKouho(int n, int k_f){
    if(masu[n].kouho[k_f])return 1;
    return 0;
}

/*  kouho:k_f が同じLineに1つのみならreturn1*/
int isOnlyOneInLine(int n, int k_f){
    int i;
    int sum = 0;
    int ls = lineStart(n);
    for(i=0; i<9; i++){
        if(masu[ls+i].kouho[k_f])sum++;
    }
    if(sum == 1){
        return 1;
    }
    return 0;
}

int isOnlyOneInRow(int n, int k_f){
    int i;
    int sum = 0;
    int rs = rowStart(n);
    for(i=0; i<81; i+=9){
        if(masu[rs+i].kouho[k_f])sum++;
    }
    if(sum == 1){
        return 1;
    }
    return 0;
}


int isOnlyOneInBlock(int n, int k_f){
    int i, j;
    int sum = 0;
    int bs = blockStart(n);
    for(i=0; i<27; i+=9){
        for(j=0; j<3; j++){
            if(masu[bs+i+j].kouho[k_f])sum++;
        }
    }
    if(sum == 1){
        return 1;
    }
    return 0;
}

int isOnlyOne(int n, int k_f){
    int a = isOnlyOneInLine(n, k_f);
    int b = isOnlyOneInRow(n, k_f);
    int c = isOnlyOneInBlock(n, k_f); 
    //printw("(%d+%d+%d=)",a,b,c);
    return a+b+c;
}