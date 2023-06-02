#include "settings.h"
#include "ncurses.h"

void screen_setup(){
    initscr(); // 윈도우 초기화
    noecho(); // 입력된 키를 화면에 표시 x
    curs_set(0); // 커서 심볼을 화면에 표시 x
    keypad(stdscr, TRUE); // 터미널에 특수 키 입력을 활성화(방향키)
    cbreak(); // 특수키 입력을 즉시 처리(엔터키를 누르지 않아도 키를 누르자마자 처리)
    nodelay(stdscr, TRUE); // 키 입력을 기다리지 않고 바로 반환
}
// 스크린 종료 전 처리
void screen_teardown(){
    echo(); // 입력된 키를 화면에 표시 o
    curs_set(1); // 커서 심볼을 화면에 표시 o
    endwin(); // 윈도우 종료
}

void init_pair_colors(){
    init_pair(1, COLOR_BLACK, COLOR_BLACK); // filed
    init_pair(2, COLOR_WHITE, COLOR_WHITE); // immune wall
    init_pair(3, COLOR_GREEN, COLOR_GREEN); // wall
    init_pair(5, COLOR_BLUE, COLOR_BLUE); // Growth
    init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA); // Poison
    init_pair(11, COLOR_YELLOW, COLOR_YELLOW); // head
    init_pair(12, COLOR_CYAN, COLOR_CYAN); // tail
}