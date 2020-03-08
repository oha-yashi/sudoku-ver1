#include <ncurses.h>
#include "menu.h"
#include "setting.h"
#include "calc.h"

/*  Line|Row Show
    showAll系に対応した表示座標
    markNowで使う*/
int LS[9] = {0,1,2,4,5,6,8,9,10};
int RS[9] = {1,5,9,15,19,23,29,33,37};

void menu(){
    ch = now = 0;
    while(1){
        int i;
        findAllOnlyOne();
        showAllTest();
        markNow(now);
        printmenu();
        ch = getch();
        if(ch == 'q'){
            break;
        }else if(ch == 'k'){
            int i;
            for(i=0; i<9; i++){
                showAllKouho(i);
                getch();
            }
        }else if(ch == 'c'){
            changeKouho();
        }else if(ch == ' '){
            now++;
            if(now==81)now=0;
        }else if(KEY_DOWN <= ch && ch <= KEY_RIGHT){
            addch('\n');udrl(ch);
        }else if('0' <= ch && ch <= '9'){
            inputNum(now, ch - '0');
            printw("%d\n", ch - '0');
            now++;
            if(now==81)now=0;
        }
        else{
            printw("%d\n", ch);
        }
        checkNumAll();
        refresh();

    }
}

void printmenu(){
    int i;
    move(12,0);
    printw("now(%d, %d, in %d): ",
    LINE(now), ROW(now), BLOCK(now));
    if(masu[now].num > -1){
        printw("[%d] < ", masu[now].num + 1);
    }else{
        printw("[_] < ");
    }
    for(i=0; i<9; i++){
        if(masu[now].kouho[i]){
            printw("%d ", i+1);
        }
    }
    addstr(">\n");
    addstr("[^] [v] [<] [>] [Space] [");
    reverse(ON);addch('K');reverse(OFF);
    addstr("ouho] [");
    reverse(ON);addch('F');reverse(OFF);
    addstr("ind] [");
    reverse(ON);addch('C');reverse(OFF);
    addstr("hange] [");
    //reverse(ON);addch('S');reverse(OFF);
    //addstr("how] [");
    reverse(ON);addch('Q');reverse(OFF);
    addstr("uit]");
    refresh();
}

void udrl(int ch){
    switch(ch){
        case KEY_UP:
            now = LINE(now)!=0 ? now-9 : now+72;
            break;
        case KEY_DOWN:
            now = LINE(now)!=8 ? now+9 : now-72;
            break;
        case KEY_LEFT:
            now = ROW(now)!=0 ? now-1 : now+8;
            break;
        case KEY_RIGHT:
            now = ROW(now)!=8 ? now+1 : now-8;
            break;
    }
}

void markNow(int n){
    attron(COLOR_PAIR(2));
    mvprintw(LS[LINE(n)], RS[ROW(n)]-1, "$");
    mvprintw(LS[LINE(n)], RS[ROW(n)]+1, "$");
    attron(COLOR_PAIR(1));
}

void findAllOnlyOne(){
    int i, j;
    for(i=0; i<81; i++){
        for(j=0; j<9; j++){
            if(masu[i].kouho[j]){
                if(isOnlyOne(i, j)){
                    inputNum(i, j+1);
                }
            }
        }
    }
}

void changeKouho(){
    int i, change;
    move(13,0);
    for(i=0; i<9; i++){
        if(masu[now].kouho[i]){
            printw("%d ", i+1);
        }
    }
    addstr("whitch to change -> ");
    change = getch() - '1';
    if(0 <= change && change <= 8){
        masu[now].kouho[change] = masu[now].kouho[change] ? 0 : 1;
    }
    printw("%d\n", change+1);
}