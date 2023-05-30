#include <iostream>
#include <fstream>
#include "ncurses.h"
#include "map.h"
using namespace std;

Map::Map(string file_name)
{
    ifstream file(file_name);
    int number;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            file >> number;
            map_stat[i][j] = number;
        }
    }
    file.close();
}

void Map::test()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {

            cout << map_stat[i][j] << " ";
        }
        cout << endl;
    }
}

WINDOW *Map::init()
{
    start_color();
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    WINDOW *wMap = subwin(stdscr, N, N, 0, 0);

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            attron(COLOR_PAIR(map_stat[row][col] + 1));
            printw("  ");
        }
        printw("\n");
    }

    wrefresh(wMap);
    return wMap;
}
