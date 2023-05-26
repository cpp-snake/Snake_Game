#include <iostream>
#include "ncurses.h"
#define max_x 21
#define max_y 21

int main()
{
    int map[max_x][max_y] = {0};
    for (int i = 0; i < max_x; i++)
    {
        map[i][0] = 1;
        map[i][max_y - 1] = 1;
    }
    for (int i = 0; i < max_y; i++)
    {
        map[0][i] = 1;
        map[max_x - 1][i] = 1;
    }
    map[0][0] = 2;
    map[0][max_y - 1] = 2;
    map[max_x - 1][0] = 2;
    map[max_x - 1][max_y - 1] = 2;
    initscr();
    start_color();
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    for (int i = 0; i < max_x; i++)
    {
        for (int j = 0; j < max_y; j++)
        {
            attron(COLOR_PAIR(map[i][j] + 1));
            printw("  ", map[i][j]);
        }
        printw("\n");
    }
    refresh();
    getch();
    endwin();
    return 0;
}