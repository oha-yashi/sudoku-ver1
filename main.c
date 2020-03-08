#include <ncurses.h>
#include "setting.h"
#include "calc.h"
#include "menu.h"

int main(void){
    startGame();

    reset();
    getch();

    menu();

    showAllTest();

    getch();
    endGame();
    return 0;
}