#include "ncurses.h"
#include "map.h"

int main()
{
    Map map("map_design.txt");
    initscr();
    map.init();
    getch();
    endwin();
    return 0;
}