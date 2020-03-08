#ifndef _SETTING_H_
#define _SETTING_H_

#define YOKO 77 /* マスの横幅 */
#define TATE 37 /* マスの行数 */
#define YOKO_ALL (YOKO+1) /* 必要な横幅 */
#define TATE_ALL (TATE+3) /* 必要な行数 */

#define ON 1
#define OFF 0

/* 上下左右キーマクロ
 * ^: KEY_UP
 * v: KEY_DOWN
 * <: KEY_LEFT
 * >: KEY_RIGHT
 */

/* 色設定で使用。ncursesの定数とぶつからない命名 */
#define colorBLACK 0
#define colorRED 9
#define colorGREEN 10 
#define colorWHITE 231

void startGame();
void colorSetting();
int checkWindowSize();
void endGame();
void reverse(int);

#endif